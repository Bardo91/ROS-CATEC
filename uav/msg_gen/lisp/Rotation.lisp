; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Rotation.msg.html

(cl:defclass <Rotation> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (status
    :reader status
    :initarg :status
    :type cl:boolean
    :initform cl:nil)
   (quality
    :reader quality
    :initarg :quality
    :type cl:integer
    :initform 0)
   (rotation
    :reader rotation
    :initarg :rotation
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass Rotation (<Rotation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Rotation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Rotation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Rotation> is deprecated: use uav-msg:Rotation instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <Rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:status-val is deprecated.  Use uav-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <Rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:quality-val is deprecated.  Use uav-msg:quality instead.")
  (quality m))

(cl:ensure-generic-function 'rotation-val :lambda-list '(m))
(cl:defmethod rotation-val ((m <Rotation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:rotation-val is deprecated.  Use uav-msg:rotation instead.")
  (rotation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Rotation>) ostream)
  "Serializes a message object of type '<Rotation>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'rotation) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Rotation>) istream)
  "Deserializes a message object of type '<Rotation>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'rotation) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Rotation>)))
  "Returns string type for a message object of type '<Rotation>"
  "uav/Rotation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Rotation)))
  "Returns string type for a message object of type 'Rotation"
  "uav/Rotation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Rotation>)))
  "Returns md5sum for a message object of type '<Rotation>"
  "467f1f2fc6dfd8b94cb8b38591341219")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Rotation)))
  "Returns md5sum for a message object of type 'Rotation"
  "467f1f2fc6dfd8b94cb8b38591341219")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Rotation>)))
  "Returns full string definition for message of type '<Rotation>"
  (cl:format cl:nil "Header header~%bool status~%byte quality~%geometry_msgs/Vector3 rotation~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Rotation)))
  "Returns full string definition for message of type 'Rotation"
  (cl:format cl:nil "Header header~%bool status~%byte quality~%geometry_msgs/Vector3 rotation~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Rotation>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'rotation))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Rotation>))
  "Converts a ROS message object to a list"
  (cl:list 'Rotation
    (cl:cons ':header (header msg))
    (cl:cons ':status (status msg))
    (cl:cons ':quality (quality msg))
    (cl:cons ':rotation (rotation msg))
))
