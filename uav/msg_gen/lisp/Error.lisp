; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Error.msg.html

(cl:defclass <Error> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (level
    :reader level
    :initarg :level
    :type cl:fixnum
    :initform 0)
   (errorMessage
    :reader errorMessage
    :initarg :errorMessage
    :type cl:string
    :initform ""))
)

(cl:defclass Error (<Error>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Error>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Error)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Error> is deprecated: use uav-msg:Error instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Error>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'level-val :lambda-list '(m))
(cl:defmethod level-val ((m <Error>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:level-val is deprecated.  Use uav-msg:level instead.")
  (level m))

(cl:ensure-generic-function 'errorMessage-val :lambda-list '(m))
(cl:defmethod errorMessage-val ((m <Error>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:errorMessage-val is deprecated.  Use uav-msg:errorMessage instead.")
  (errorMessage m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Error>)))
    "Constants for message type '<Error>"
  '((:WARNING . 0)
    (:IMPORTANT . 1)
    (:CRITICAL . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Error)))
    "Constants for message type 'Error"
  '((:WARNING . 0)
    (:IMPORTANT . 1)
    (:CRITICAL . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Error>) ostream)
  "Serializes a message object of type '<Error>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'level)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'errorMessage))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'errorMessage))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Error>) istream)
  "Deserializes a message object of type '<Error>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'level) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'errorMessage) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'errorMessage) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Error>)))
  "Returns string type for a message object of type '<Error>"
  "uav/Error")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Error)))
  "Returns string type for a message object of type 'Error"
  "uav/Error")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Error>)))
  "Returns md5sum for a message object of type '<Error>"
  "3d0c13397c6a13e46fb83640aa6536ea")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Error)))
  "Returns md5sum for a message object of type 'Error"
  "3d0c13397c6a13e46fb83640aa6536ea")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Error>)))
  "Returns full string definition for message of type '<Error>"
  (cl:format cl:nil "Header header~%int8 level~%int8 WARNING=0~%int8 IMPORTANT=1~%int8 CRITICAL=2~%string errorMessage~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Error)))
  "Returns full string definition for message of type 'Error"
  (cl:format cl:nil "Header header~%int8 level~%int8 WARNING=0~%int8 IMPORTANT=1~%int8 CRITICAL=2~%string errorMessage~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Error>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     4 (cl:length (cl:slot-value msg 'errorMessage))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Error>))
  "Converts a ROS message object to a list"
  (cl:list 'Error
    (cl:cons ':header (header msg))
    (cl:cons ':level (level msg))
    (cl:cons ':errorMessage (errorMessage msg))
))
