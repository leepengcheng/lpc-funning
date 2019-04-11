#!/usr/bin/env python
# coding:utf-8
import glob
import os
import sys
try:
    sys.path.append(
        glob.glob('../carla/dist/carla-*%d.%d-%s.egg' %
                  (sys.version_info.major, sys.version_info.minor,
                   'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])
except IndexError:
    pass

import carla
import random
import time
import math
import cv2
import numpy as np
import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import Float32
from cv_bridge import CvBridge
import weakref

class CanBus(object):
    def __init__(self, world, actors):
        rospy.init_node("carla_node", disable_signals=True)
        self.image_pub = rospy.Publisher("/carla/image", Image, queue_size=20)
        self.info_pub = rospy.Publisher("/carla/carinfo",
                                        Float32,
                                        queue_size=20)
        self.cmd_sub = rospy.Subscriber("/carla/carcmd",
                                        Float32,
                                        callback=self.onReceiveCarCmd)
        self.bridge = CvBridge()
        self.carControl = carla.VehicleControl(throttle=1.0, steer=0.0)
        self.world = world
        self.actors = actors
        self.infoMsg = {"speed": 0}
        self.imageMsg = Image()
        self.setCamListenCallBack()
        self.setWorldTickCallBack()


    def setWorldTickCallBack(self):
        self.world.on_tick(self.onTickUpdateInfo)

    def setCamListenCallBack(self):
        self.actors["camera"].listen(self.parse_image)

    def onTickUpdateInfo(self, t):
        vel = self.actors["vehicle"].get_velocity()
        vel = 3.6 * math.sqrt(vel.x**2 + vel.y**2 + vel.z**2)
        self.infoMsg["speed"] = vel
        if vel>60.0:
            self.carControl.brake=0.5
        self.actors["vehicle"].apply_control(self.carControl)


    def onReceiveCarCmd(self, msg):
        print(msg)
        self.carControl.throttle = msg.data

    def parse_image(self, image):
        image.convert(carla.ColorConverter.Raw)
        np_img = np.frombuffer(image.raw_data, dtype=np.dtype("uint8"))
        np_img = np.reshape(np_img, (image.height, image.width, 4))
        self.imageMsg = self.bridge.cv2_to_imgmsg(np_img[:, :, :3], "bgr8")
        # image.save_to_disk('_out/%08d' % image.frame_number)

    def publishMessage(self):
        self.image_pub.publish(self.imageMsg)
        self.info_pub.publish(self.infoMsg["speed"])
    
    def destroy(self):
        pass


def main():
    actors = {}  #actor_list中的actor销毁需要手动调用destroy
    try:
        #连接服务器
        client = carla.Client('localhost', 2000)
        client.set_timeout(2.0)

        # 获取环境
        world = client.get_world()
        blueprint_library = world.get_blueprint_library()

        #选择一个vehicle actor蓝图
        bp_libs = blueprint_library.filter('vehicle')
        # for x in bp_libs:
        #     print(x.id)
        bp = bp_libs[14]  # tesla model 3

        # 设置actor蓝图的颜色(不同的车不一样)
        if bp.has_attribute('color'):
            colors = bp.get_attribute('color').recommended_values
            color = colors[0]
            bp.set_attribute('color', color)

        #指定位置创建车辆
        # avail_pts=world.get_map().get_spawn_points() #预先设置的点
        transform = carla.Transform(carla.Location(x=20, y=-4.0, z=1.0))
        vehicle = world.spawn_actor(bp, transform)
        vehicle.set_autopilot(False)  #设置是否自动驾驶
        actors["vehicle"] = vehicle
        print('created %s' % vehicle.type_id)

        #指定位置创建rgb相机
        rgbcam_bp = blueprint_library.find('sensor.camera.rgb')  #获取rgb传感器
        # # rgbcam_bp.set_attribute('image_size_x', "640")  #默认是800*600
        # # rgbcam_bp.set_attribute('image_size_y', "360")
        # # rgbcam_bp.set_attribute('fov', "60.0")     #默认fov=90.0
        cam_transform = carla.Transform(carla.Location(
            x=1.5, z=2.4))  #设置传感器的位置(相对与于车辆)
        camera = world.spawn_actor(rgbcam_bp, cam_transform, attach_to=vehicle)
        actors["camera"] = camera  #记录actor
        print('created %s' % camera.type_id)

        ##################设置车辆的位置###############
        # location = vehicle.get_location() #获取车辆位置
        # vehicle.set_location(location)  #设置车辆位置的的
        # print('moved vehicle to %s' % location)

        ######################创建随机车辆############
        # transform.location += carla.Location(x=40, y=-3.2)
        # transform.rotation.yaw = -180.0
        # for _ in range(0, 10):
        #     transform.location.x += 8.0
        #     bp = random.choice(blueprint_library.filter('vehicle'))
        #     npc = world.try_spawn_actor(bp, transform)
        #     if npc is not None:
        #         actors.append(npc)
        #         npc.set_autopilot()ww
        #         print('created %s' % npc.type_id)
        canbus = CanBus(world, actors)
        while True:
            if not world.wait_for_tick():
                continue
            canbus.publishMessage()
    except KeyboardInterrupt:
        pass
    finally:
        for actor in actors.values():
            actor.destroy()
        print('destroy actors')


if __name__ == "__main__":
    main()
