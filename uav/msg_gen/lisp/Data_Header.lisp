; Auto-generated. Do not edit!


(cl:in-package uav-msg)


;//! \htmlinclude Data_Header.msg.html

(cl:defclass <Data_Header> (roslisp-msg-protocol:ros-message)
  ((seq
    :reader seq
    :initarg :seq
    :type cl:integer
    :initform 0)
   (stamp
    :reader stamp
    :initarg :stamp
    :type cl:float
    :initform 0.0)
   (frame_id
    :reader frame_id
    :initarg :frame_id
    :type cl:string
    :initform "")
   (status
    :reader status
    :initarg :status
    :type cl:boolean
    :initform cl:nil)
   (quality
    :reader quality
    :initarg :quality
    :type cl:integer
    :initform 0))
)

(cl:defclass Data_Header (<Data_Header>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Data_Header>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Data_Header)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav-msg:<Data_Header> is deprecated: use uav-msg:Data_Header instead.")))

(cl:ensure-generic-function 'seq-val :lambda-list '(m))
(cl:defmethod seq-val ((m <Data_Header>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:seq-val is deprecated.  Use uav-msg:seq instead.")
  (seq m))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <Data_Header>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:stamp-val is deprecated.  Use uav-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'frame_id-val :lambda-list '(m))
(cl:defmethod frame_id-val ((m <Data_Header>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:frame_id-val is deprecated.  Use uav-msg:frame_id instead.")
  (frame_id m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <Data_Header>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:status-val is deprecated.  Use uav-msg:status instead.")
  (status m))

(cl:ensure-generic-function 'quality-val :lambda-list '(m))
(cl:defmethod quality-val ((m <Data_Header>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav-msg:quality-val is deprecated.  Use uav-msg:quality instead.")
  (quality m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Data_Header>) ostream)
  "Serializes a message object of type '<Data_Header>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seq)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'stamp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'frame_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'frame_id))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'status) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Data_Header>) istream)
  "Deserializes a message object of type '<Data_Header>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'stamp) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frame_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'frame_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'status) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quality)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Data_Header>)))
  "Returns string type for a message object of type '<Data_Header>"
  "uav/Data_Header")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Data_Header)))
  "Returns string type for a message object of type 'Data_Header"
  "uav/Data_Header")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Data_Header>)))
  "Returns md5sum for a message object of type '<Data_Header>"
  "e475a694e3cb9e70aac3eb08dae30d26")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Data_Header)))
  "Returns md5sum for a message object of type 'Data_Header"
  "e475a694e3cb9e70aac3eb08dae30d26")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Data_Header>)))
  "Returns full string definition for message of type '<Data_Header>"
  (cl:format cl:nil "uint32 seq~%float64 stamp~%string frame_id~%bool status~%byte quality~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Data_Header)))
  "Returns full string definition for message of type 'Data_Header"
  (cl:format cl:nil "uint32 seq~%float64 stamp~%string frame_id~%bool status~%byte quality~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Data_Header>))
  (cl:+ 0
     4
     8
     4 (cl:length (cl:slot-value msg 'frame_id))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Data_Header>))
  "Converts a ROS message object to a list"
  (cl:list 'Data_Header
    (cl:cons ':seq (seq msg))
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':frame_id (frame_id msg))
    (cl:cons ':status (status msg))
    (cl:cons ':quality (quality msg))
))
