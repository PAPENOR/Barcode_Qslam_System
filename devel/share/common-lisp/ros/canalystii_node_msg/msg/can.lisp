; Auto-generated. Do not edit!


(cl:in-package canalystii_node_msg-msg)


;//! \htmlinclude can.msg.html

(cl:defclass <can> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (id
    :reader id
    :initarg :id
    :type cl:integer
    :initform 0)
   (timeflag
    :reader timeflag
    :initarg :timeflag
    :type cl:integer
    :initform 0)
   (sendtype
    :reader sendtype
    :initarg :sendtype
    :type cl:fixnum
    :initform 0)
   (remoteflag
    :reader remoteflag
    :initarg :remoteflag
    :type cl:fixnum
    :initform 0)
   (externflag
    :reader externflag
    :initarg :externflag
    :type cl:fixnum
    :initform 0)
   (datalen
    :reader datalen
    :initarg :datalen
    :type cl:fixnum
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass can (<can>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <can>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'can)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name canalystii_node_msg-msg:<can> is deprecated: use canalystii_node_msg-msg:can instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:header-val is deprecated.  Use canalystii_node_msg-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:id-val is deprecated.  Use canalystii_node_msg-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'timeflag-val :lambda-list '(m))
(cl:defmethod timeflag-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:timeflag-val is deprecated.  Use canalystii_node_msg-msg:timeflag instead.")
  (timeflag m))

(cl:ensure-generic-function 'sendtype-val :lambda-list '(m))
(cl:defmethod sendtype-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:sendtype-val is deprecated.  Use canalystii_node_msg-msg:sendtype instead.")
  (sendtype m))

(cl:ensure-generic-function 'remoteflag-val :lambda-list '(m))
(cl:defmethod remoteflag-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:remoteflag-val is deprecated.  Use canalystii_node_msg-msg:remoteflag instead.")
  (remoteflag m))

(cl:ensure-generic-function 'externflag-val :lambda-list '(m))
(cl:defmethod externflag-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:externflag-val is deprecated.  Use canalystii_node_msg-msg:externflag instead.")
  (externflag m))

(cl:ensure-generic-function 'datalen-val :lambda-list '(m))
(cl:defmethod datalen-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:datalen-val is deprecated.  Use canalystii_node_msg-msg:datalen instead.")
  (datalen m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <can>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader canalystii_node_msg-msg:data-val is deprecated.  Use canalystii_node_msg-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <can>) ostream)
  "Serializes a message object of type '<can>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timeflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timeflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timeflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timeflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sendtype)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remoteflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'externflag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'datalen)) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <can>) istream)
  "Deserializes a message object of type '<can>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'timeflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'timeflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'timeflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'timeflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'sendtype)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'remoteflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'externflag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'datalen)) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i 8)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<can>)))
  "Returns string type for a message object of type '<can>"
  "canalystii_node_msg/can")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'can)))
  "Returns string type for a message object of type 'can"
  "canalystii_node_msg/can")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<can>)))
  "Returns md5sum for a message object of type '<can>"
  "e974a5e243febe68ac8618d673926338")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'can)))
  "Returns md5sum for a message object of type 'can"
  "e974a5e243febe68ac8618d673926338")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<can>)))
  "Returns full string definition for message of type '<can>"
  (cl:format cl:nil "Header header~%uint32 id~%uint32 timeflag~%uint8 sendtype~%uint8 remoteflag~%uint8 externflag~%uint8 datalen~%uint8[8] data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'can)))
  "Returns full string definition for message of type 'can"
  (cl:format cl:nil "Header header~%uint32 id~%uint32 timeflag~%uint8 sendtype~%uint8 remoteflag~%uint8 externflag~%uint8 datalen~%uint8[8] data~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <can>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     1
     1
     1
     1
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <can>))
  "Converts a ROS message object to a list"
  (cl:list 'can
    (cl:cons ':header (header msg))
    (cl:cons ':id (id msg))
    (cl:cons ':timeflag (timeflag msg))
    (cl:cons ':sendtype (sendtype msg))
    (cl:cons ':remoteflag (remoteflag msg))
    (cl:cons ':externflag (externflag msg))
    (cl:cons ':datalen (datalen msg))
    (cl:cons ':data (data msg))
))
