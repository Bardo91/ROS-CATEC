; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude FlightPlan.msg.html

(cl:defclass <FlightPlan> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (modeFp
    :reader modeFp
    :initarg :modeFp
    :type cl:fixnum
    :initform 0)
   (position
    :reader position
    :initarg :position
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 3 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (weight
    :reader weight
    :initarg :weight
    :type cl:float
    :initform 0.0)
   (velFlightPlan
    :reader velFlightPlan
    :initarg :velFlightPlan
    :type cl:float
    :initform 0.0)
   (hFlightPlan
    :reader hFlightPlan
    :initarg :hFlightPlan
    :type cl:float
    :initform 0.0)
   (courseFlightPlan
    :reader courseFlightPlan
    :initarg :courseFlightPlan
    :type cl:float
    :initform 0.0)
   (headingFlightPlan
    :reader headingFlightPlan
    :initarg :headingFlightPlan
    :type cl:float
    :initform 0.0))
)

(cl:defclass FlightPlan (<FlightPlan>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FlightPlan>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FlightPlan)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<FlightPlan> is deprecated: use uav-msg:FlightPlan instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:header-val is deprecated.  Use uav-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'modeFp-val :lambda-list '(m))
(cl:defmethod modeFp-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:modeFp-val is deprecated.  Use uav-msg:modeFp instead.")
  (modeFp m))

(cl:ensure-generic-function 'position-val :lambda-list '(m))
(cl:defmethod position-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:position-val is deprecated.  Use uav-msg:position instead.")
  (position m))

(cl:ensure-generic-function 'weight-val :lambda-list '(m))
(cl:defmethod weight-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:weight-val is deprecated.  Use uav-msg:weight instead.")
  (weight m))

(cl:ensure-generic-function 'velFlightPlan-val :lambda-list '(m))
(cl:defmethod velFlightPlan-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:velFlightPlan-val is deprecated.  Use uav-msg:velFlightPlan instead.")
  (velFlightPlan m))

(cl:ensure-generic-function 'hFlightPlan-val :lambda-list '(m))
(cl:defmethod hFlightPlan-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:hFlightPlan-val is deprecated.  Use uav-msg:hFlightPlan instead.")
  (hFlightPlan m))

(cl:ensure-generic-function 'courseFlightPlan-val :lambda-list '(m))
(cl:defmethod courseFlightPlan-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:courseFlightPlan-val is deprecated.  Use uav-msg:courseFlightPlan instead.")
  (courseFlightPlan m))

(cl:ensure-generic-function 'headingFlightPlan-val :lambda-list '(m))
(cl:defmethod headingFlightPlan-val ((m <FlightPlan>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:headingFlightPlan-val is deprecated.  Use uav-msg:headingFlightPlan instead.")
  (headingFlightPlan m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<FlightPlan>)))
    "Constants for message type '<FlightPlan>"
  '((:POSITIONHEADINGMODE . 1)
    (:VELOCITYMODE . 2)
    (:VELOCITYHEADINGMODE . 3)
    (:POSITIONMODE . 4)
    (:POSITIONHEADINGMODEWITHVELOCITY . 5)
    (:POSITIONMODEWITHVELOCITY . 6))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'FlightPlan)))
    "Constants for message type 'FlightPlan"
  '((:POSITIONHEADINGMODE . 1)
    (:VELOCITYMODE . 2)
    (:VELOCITYHEADINGMODE . 3)
    (:POSITIONMODE . 4)
    (:POSITIONHEADINGMODEWITHVELOCITY . 5)
    (:POSITIONMODEWITHVELOCITY . 6))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FlightPlan>) ostream)
  "Serializes a message object of type '<FlightPlan>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modeFp)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'position))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'weight))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velFlightPlan))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'hFlightPlan))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'courseFlightPlan))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'headingFlightPlan))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FlightPlan>) istream)
  "Deserializes a message object of type '<FlightPlan>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'modeFp)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'position) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'position)))
    (cl:dotimes (i 3)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'weight) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velFlightPlan) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'hFlightPlan) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'courseFlightPlan) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'headingFlightPlan) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FlightPlan>)))
  "Returns string type for a message object of type '<FlightPlan>"
  "uav/FlightPlan")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FlightPlan)))
  "Returns string type for a message object of type 'FlightPlan"
  "uav/FlightPlan")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FlightPlan>)))
  "Returns md5sum for a message object of type '<FlightPlan>"
  "476a9ca065e1e22ead3921e8ce01d228")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FlightPlan)))
  "Returns md5sum for a message object of type 'FlightPlan"
  "476a9ca065e1e22ead3921e8ce01d228")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FlightPlan>)))
  "Returns full string definition for message of type '<FlightPlan>"
  (cl:format cl:nil "Header header~%uint8 modeFp~%uint8 POSITIONHEADINGMODE=1~%uint8 VELOCITYMODE=2~%uint8 VELOCITYHEADINGMODE=3~%uint8 POSITIONMODE=4~%uint8 POSITIONHEADINGMODEWITHVELOCITY=5~%uint8 POSITIONMODEWITHVELOCITY=6~%geometry_msgs/Point[3] position~%float64 weight~%float64 velFlightPlan~%float64 hFlightPlan~%float64 courseFlightPlan~%float64 headingFlightPlan~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FlightPlan)))
  "Returns full string definition for message of type 'FlightPlan"
  (cl:format cl:nil "Header header~%uint8 modeFp~%uint8 POSITIONHEADINGMODE=1~%uint8 VELOCITYMODE=2~%uint8 VELOCITYHEADINGMODE=3~%uint8 POSITIONMODE=4~%uint8 POSITIONHEADINGMODEWITHVELOCITY=5~%uint8 POSITIONMODEWITHVELOCITY=6~%geometry_msgs/Point[3] position~%float64 weight~%float64 velFlightPlan~%float64 hFlightPlan~%float64 courseFlightPlan~%float64 headingFlightPlan~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FlightPlan>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'position) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FlightPlan>))
  "Converts a ROS message object to a list"
  (cl:list 'FlightPlan
    (cl:cons ':header (header msg))
    (cl:cons ':modeFp (modeFp msg))
    (cl:cons ':position (position msg))
    (cl:cons ':weight (weight msg))
    (cl:cons ':velFlightPlan (velFlightPlan msg))
    (cl:cons ':hFlightPlan (hFlightPlan msg))
    (cl:cons ':courseFlightPlan (courseFlightPlan msg))
    (cl:cons ':headingFlightPlan (headingFlightPlan msg))
))
