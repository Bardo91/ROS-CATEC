; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Space_Configuration.msg.html

(cl:defclass <Space_Configuration> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (scalar
    :reader scalar
    :initarg :scalar
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (northAngle
    :reader northAngle
    :initarg :northAngle
    :type cl:float
    :initform 0.0)
   (utmLongitude
    :reader utmLongitude
    :initarg :utmLongitude
    :type cl:float
    :initform 0.0)
   (utmLatitude
    :reader utmLatitude
    :initarg :utmLatitude
    :type cl:float
    :initform 0.0)
   (utmHeight
    :reader utmHeight
    :initarg :utmHeight
    :type cl:float
    :initform 0.0))
)

(cl:defclass Space_Configuration (<Space_Configuration>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Space_Configuration>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Space_Configuration)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Space_Configuration> is deprecated: use uav-msg:Space_Configuration instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'scalar-val :lambda-list '(m))
(cl:defmethod scalar-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:scalar-val is deprecated.  Use uav-msg:scalar instead.")
  (scalar m))

(cl:ensure-generic-function 'northAngle-val :lambda-list '(m))
(cl:defmethod northAngle-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:northAngle-val is deprecated.  Use uav-msg:northAngle instead.")
  (northAngle m))

(cl:ensure-generic-function 'utmLongitude-val :lambda-list '(m))
(cl:defmethod utmLongitude-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:utmLongitude-val is deprecated.  Use uav-msg:utmLongitude instead.")
  (utmLongitude m))

(cl:ensure-generic-function 'utmLatitude-val :lambda-list '(m))
(cl:defmethod utmLatitude-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:utmLatitude-val is deprecated.  Use uav-msg:utmLatitude instead.")
  (utmLatitude m))

(cl:ensure-generic-function 'utmHeight-val :lambda-list '(m))
(cl:defmethod utmHeight-val ((m <Space_Configuration>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:utmHeight-val is deprecated.  Use uav-msg:utmHeight instead.")
  (utmHeight m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Space_Configuration>) ostream)
  "Serializes a message object of type '<Space_Configuration>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'scalar) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'northAngle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utmLongitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utmLatitude))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'utmHeight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Space_Configuration>) istream)
  "Deserializes a message object of type '<Space_Configuration>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'scalar) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'northAngle) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utmLongitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utmLatitude) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'utmHeight) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Space_Configuration>)))
  "Returns string type for a message object of type '<Space_Configuration>"
  "uav/Space_Configuration")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Space_Configuration)))
  "Returns string type for a message object of type 'Space_Configuration"
  "uav/Space_Configuration")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Space_Configuration>)))
  "Returns md5sum for a message object of type '<Space_Configuration>"
  "b4122defdaa459823c428e4bcf09d468")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Space_Configuration)))
  "Returns md5sum for a message object of type 'Space_Configuration"
  "b4122defdaa459823c428e4bcf09d468")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Space_Configuration>)))
  "Returns full string definition for message of type '<Space_Configuration>"
  (cl:format cl:nil "Header header~%geometry_msgs/Vector3 scalar~%float64 northAngle~%float64 utmLongitude~%float64 utmLatitude~%float64 utmHeight~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Space_Configuration)))
  "Returns full string definition for message of type 'Space_Configuration"
  (cl:format cl:nil "Header header~%geometry_msgs/Vector3 scalar~%float64 northAngle~%float64 utmLongitude~%float64 utmLatitude~%float64 utmHeight~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Space_Configuration>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'scalar))
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Space_Configuration>))
  "Converts a ROS message object to a list"
  (cl:list 'Space_Configuration
    (cl:cons ':header (header msg))
    (cl:cons ':scalar (scalar msg))
    (cl:cons ':northAngle (northAngle msg))
    (cl:cons ':utmLongitude (utmLongitude msg))
    (cl:cons ':utmLatitude (utmLatitude msg))
    (cl:cons ':utmHeight (utmHeight msg))
))
