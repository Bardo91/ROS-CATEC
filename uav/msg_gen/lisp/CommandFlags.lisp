; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude CommandFlags.msg.html

(cl:defclass <CommandFlags> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (flags
    :reader flags
    :initarg :flags
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 8 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass CommandFlags (<CommandFlags>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CommandFlags>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CommandFlags)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<CommandFlags> is deprecated: use uav-msg:CommandFlags instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CommandFlags>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'flags-val :lambda-list '(m))
(cl:defmethod flags-val ((m <CommandFlags>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:flags-val is deprecated.  Use uav-msg:flags instead.")
  (flags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CommandFlags>) ostream)
  "Serializes a message object of type '<CommandFlags>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'flags))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CommandFlags>) istream)
  "Deserializes a message object of type '<CommandFlags>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'flags) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'flags)))
    (cl:dotimes (i 8)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CommandFlags>)))
  "Returns string type for a message object of type '<CommandFlags>"
  "uav/CommandFlags")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CommandFlags)))
  "Returns string type for a message object of type 'CommandFlags"
  "uav/CommandFlags")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CommandFlags>)))
  "Returns md5sum for a message object of type '<CommandFlags>"
  "477052cb4fa5501822d3a6618109ce30")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CommandFlags)))
  "Returns md5sum for a message object of type 'CommandFlags"
  "477052cb4fa5501822d3a6618109ce30")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CommandFlags>)))
  "Returns full string definition for message of type '<CommandFlags>"
  (cl:format cl:nil "Header header~%bool[8] flags~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CommandFlags)))
  "Returns full string definition for message of type 'CommandFlags"
  (cl:format cl:nil "Header header~%bool[8] flags~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CommandFlags>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'flags) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CommandFlags>))
  "Converts a ROS message object to a list"
  (cl:list 'CommandFlags
    (cl:cons ':header (header msg))
    (cl:cons ':flags (flags msg))
))
