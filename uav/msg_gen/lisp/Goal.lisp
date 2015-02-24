; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Goal.msg.html

(cl:defclass <Goal> (roslisp-msg-protocol:ros-message)
  ((gohere
    :reader gohere
    :initarg :gohere
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass Goal (<Goal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Goal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Goal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Goal> is deprecated: use uav-msg:Goal instead.")))

(cl:ensure-generic-function 'gohere-val :lambda-list '(m))
(cl:defmethod gohere-val ((m <Goal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:gohere-val is deprecated.  Use uav-msg:gohere instead.")
  (gohere m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Goal>) ostream)
  "Serializes a message object of type '<Goal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'gohere) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Goal>) istream)
  "Deserializes a message object of type '<Goal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'gohere) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Goal>)))
  "Returns string type for a message object of type '<Goal>"
  "uav/Goal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Goal)))
  "Returns string type for a message object of type 'Goal"
  "uav/Goal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Goal>)))
  "Returns md5sum for a message object of type '<Goal>"
  "c527f0c1d56ca8c26b7f7328f878a602")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Goal)))
  "Returns md5sum for a message object of type 'Goal"
  "c527f0c1d56ca8c26b7f7328f878a602")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Goal>)))
  "Returns full string definition for message of type '<Goal>"
  (cl:format cl:nil "geometry_msgs/Point gohere~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Goal)))
  "Returns full string definition for message of type 'Goal"
  (cl:format cl:nil "geometry_msgs/Point gohere~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Goal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'gohere))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Goal>))
  "Converts a ROS message object to a list"
  (cl:list 'Goal
    (cl:cons ':gohere (gohere msg))
))
