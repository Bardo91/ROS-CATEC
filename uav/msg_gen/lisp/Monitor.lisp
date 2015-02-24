; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Monitor.msg.html

(cl:defclass <Monitor> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos_status
    :reader pos_status
    :initarg :pos_status
    :type cl:boolean
    :initform cl:nil)
   (vel_status
    :reader vel_status
    :initarg :vel_status
    :type cl:boolean
    :initform cl:nil)
   (act_status
    :reader act_status
    :initarg :act_status
    :type cl:boolean
    :initform cl:nil)
   (quality
    :reader quality
    :initarg :quality
    :type cl:integer
    :initform 0)
   (pose
    :reader pose
    :initarg :pose
    :type geometry_msgs-msg:PoseWithCovariance
    :initform (cl:make-instance 'geometry_msgs-msg:PoseWithCovariance))
   (twist
    :reader twist
    :initarg :twist
    :type geometry_msgs-msg:TwistWithCovariance
    :initform (cl:make-instance 'geometry_msgs-msg:TwistWithCovariance))
   (bat_voltage
    :reader bat_voltage
    :initarg :bat_voltage
    :type cl:float
    :initform 0.0)
   (bat_current
    :reader bat_current
    :initarg :bat_current
    :type cl:float
    :initform 0.0))
)

(cl:defclass Monitor (<Monitor>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Monitor>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Monitor)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Monitor> is deprecated: use uav-msg:Monitor instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos_status-val :lambda-list '(m))
(cl:defmethod pos_status-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:pos_status-val is deprecated.  Use uav-msg:pos_status instead.")
  (pos_status m))

(cl:ensure-generic-function 'vel_status-val :lambda-list '(m))
(cl:defmethod vel_status-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:vel_status-val is deprecated.  Use uav-msg:vel_status instead.")
  (vel_status m))

(cl:ensure-generic-function 'act_status-val :lambda-list '(m))
(cl:defmethod act_status-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:act_status-val is deprecated.  Use uav-msg:act_status instead.")
  (act_status m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:quality-val is deprecated.  Use uav-msg:quality instead.")
  (quality m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:pose-val is deprecated.  Use uav-msg:pose instead.")
  (pose m))

(cl:ensure-generic-function 'twist-val :lambda-list '(m))
(cl:defmethod twist-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:twist-val is deprecated.  Use uav-msg:twist instead.")
  (twist m))

(cl:ensure-generic-function 'bat_voltage-val :lambda-list '(m))
(cl:defmethod bat_voltage-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:bat_voltage-val is deprecated.  Use uav-msg:bat_voltage instead.")
  (bat_voltage m))

(cl:ensure-generic-function 'bat_current-val :lambda-list '(m))
(cl:defmethod bat_current-val ((m <Monitor>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:bat_current-val is deprecated.  Use uav-msg:bat_current instead.")
  (bat_current m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Monitor>) ostream)
  "Serializes a message object of type '<Monitor>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pos_status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'vel_status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'act_status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'twist) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'bat_voltage))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'bat_current))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Monitor>) istream)
  "Deserializes a message object of type '<Monitor>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'pos_status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'vel_status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'act_status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'twist) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bat_voltage) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'bat_current) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Monitor>)))
  "Returns string type for a message object of type '<Monitor>"
  "uav/Monitor")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Monitor)))
  "Returns string type for a message object of type 'Monitor"
  "uav/Monitor")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Monitor>)))
  "Returns md5sum for a message object of type '<Monitor>"
  "751ee931a99632c134e9dfb1e9a2128d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Monitor)))
  "Returns md5sum for a message object of type 'Monitor"
  "751ee931a99632c134e9dfb1e9a2128d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Monitor>)))
  "Returns full string definition for message of type '<Monitor>"
  (cl:format cl:nil "Header header~%bool pos_status~%bool vel_status~%bool act_status~%byte quality~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%float64 bat_voltage~%float64 bat_current~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertianty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Monitor)))
  "Returns full string definition for message of type 'Monitor"
  (cl:format cl:nil "Header header~%bool pos_status~%bool vel_status~%bool act_status~%byte quality~%geometry_msgs/PoseWithCovariance pose~%geometry_msgs/TwistWithCovariance twist~%float64 bat_voltage~%float64 bat_current~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseWithCovariance~%# This represents a pose in free space with uncertainty.~%~%Pose pose~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/TwistWithCovariance~%# This expresses velocity in free space with uncertianty.~%~%Twist twist~%~%# Row-major representation of the 6x6 covariance matrix~%# The orientation parameters use a fixed-axis representation.~%# In order, the parameters are:~%# (x, y, z, rotation about X axis, rotation about Y axis, rotation about Z axis)~%float64[36] covariance~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into it's linear and angular parts. ~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Monitor>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'twist))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Monitor>))
  "Converts a ROS message object to a list"
  (cl:list 'Monitor
    (cl:cons ':header (header msg))
    (cl:cons ':pos_status (pos_status msg))
    (cl:cons ':vel_status (vel_status msg))
    (cl:cons ':act_status (act_status msg))
    (cl:cons ':quality (quality msg))
    (cl:cons ':pose (pose msg))
    (cl:cons ':twist (twist msg))
    (cl:cons ':bat_voltage (bat_voltage msg))
    (cl:cons ':bat_current (bat_current msg))
))
