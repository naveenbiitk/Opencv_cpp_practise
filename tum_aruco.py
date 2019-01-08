import numpy as np

class Pose3D:
    def __init__(self, rotation, translation):
        self.rotation = rotation
        self.translation = translation
        
    def inv(self):
        
        self.rotation=self.rotation.transpose()
        self.translation=-1*np.dot(self.rotation,self.translation)
        # TODO: implement inversion
        inv_rotation = self.rotation
        inv_translation = self.translation
        
        return Pose3D(inv_rotation, inv_translation)
    
    def __mul__(self, other):

        self.rotation=np.dot(self.rotation,other.rotation)
        self.translation=np.dot(self.rotation,other.translation)+self.translation
        # TODO: implement multiplication
        return Pose3D(self.rotation, self.translation)
    
    def __str__(self):
        return "rotation:\n" + str(self.rotation) + "\ntranslation:\n" + str(self.translation.transpose())

def compute_quadrotor_pose(global_marker_pose, observed_marker_pose):
        # TODO: implement global quadrotor pose computation
    global_quadrotor_pose = None
    observed_marker_pose.inv()
    global_quadrotor_pose = observed_marker_pose
    global_quadcopter_pose.__mul__(global_quadcopter_pose, observed_marker_pose)
    return global_quadrotor_pose
