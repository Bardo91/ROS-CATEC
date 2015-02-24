; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Velocity.msg.html

(cl:defclass <Velocity> (roslisp-msg-protocol:ros-message)
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
   (velocity
    :reader velocity
    :initarg :velocity
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3)))
)

(cl:defclass Velocity (<Velocity>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Velocity>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Velocity)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Velocity> is deprecated: use uav-msg:Velocity instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <Velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:status-val is deprecated.  Use uav-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <Velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:quality-val is deprecated.  Use uav-msg:quality instead.")
  (quality m))

(cl:ensure-generic-function 'velocity-val :lambda-list '(m))
(cl:defmethod velocity-val ((m <Velocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:velocity-val is deprecated.  Use uav-msg:velocity instead.")
  (velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Velocity>) ostream)
  "Serializes a message object of type '<Velocity>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'velocity) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Velocity>) istream)
  "Deserializes a message object of type '<Velocity>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'velocity) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Velocity>)))
  "Returns string type for a message object of type '<Velocity>"
  "uav/Velocity")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Velocity)))
  "Returns string type for a message object of type 'Velocity"
  "uav/Velocity")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Velocity>)))
  "Returns md5sum for a message object of type '<Velocity>"
  "7fffe7be9b6277341b56d6489f4ef270")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Velocity)))
  "Returns md5sum for a message object of type 'Velocity"
  "7fffe7be9b6277341b56d6489f4ef270")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Velocity>)))
  "Returns full string definition for message of type '<Velocity>"
  (cl:format cl:nil "Header header~%bool status~%byte quality~%geometry_msgs/Vector3 velocity~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Velocity)))
  "Returns full string definition for message of type 'Velocity"
  (cl:format cl:nil "Header header~%bool status~%byte quality~%geometry_msgs/Vector3 velocity~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Velocity>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'velocity))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Velocity>))
  "Converts a ROS message object to a list"
  (cl:list 'Velocity
    (cl:cons ':header (header msg))
    (cl:cons ':status (status msg))
    (cl:cons ':quality (quality msg))
    (cl:cons ':velocity (velocity msg))
))
