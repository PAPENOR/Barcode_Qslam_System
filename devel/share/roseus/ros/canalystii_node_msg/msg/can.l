;; Auto-generated. Do not edit!


(when (boundp 'canalystii_node_msg::can)
  (if (not (find-package "CANALYSTII_NODE_MSG"))
    (make-package "CANALYSTII_NODE_MSG"))
  (shadow 'can (find-package "CANALYSTII_NODE_MSG")))
(unless (find-package "CANALYSTII_NODE_MSG::CAN")
  (make-package "CANALYSTII_NODE_MSG::CAN"))

(in-package "ROS")
;;//! \htmlinclude can.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass canalystii_node_msg::can
  :super ros::object
  :slots (_header _id _timeflag _sendtype _remoteflag _externflag _datalen _data ))

(defmethod canalystii_node_msg::can
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:id __id) 0)
    ((:timeflag __timeflag) 0)
    ((:sendtype __sendtype) 0)
    ((:remoteflag __remoteflag) 0)
    ((:externflag __externflag) 0)
    ((:datalen __datalen) 0)
    ((:data __data) (make-array 8 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _header __header)
   (setq _id (round __id))
   (setq _timeflag (round __timeflag))
   (setq _sendtype (round __sendtype))
   (setq _remoteflag (round __remoteflag))
   (setq _externflag (round __externflag))
   (setq _datalen (round __datalen))
   (setq _data __data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:timeflag
   (&optional __timeflag)
   (if __timeflag (setq _timeflag __timeflag)) _timeflag)
  (:sendtype
   (&optional __sendtype)
   (if __sendtype (setq _sendtype __sendtype)) _sendtype)
  (:remoteflag
   (&optional __remoteflag)
   (if __remoteflag (setq _remoteflag __remoteflag)) _remoteflag)
  (:externflag
   (&optional __externflag)
   (if __externflag (setq _externflag __externflag)) _externflag)
  (:datalen
   (&optional __datalen)
   (if __datalen (setq _datalen __datalen)) _datalen)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32 _id
    4
    ;; uint32 _timeflag
    4
    ;; uint8 _sendtype
    1
    ;; uint8 _remoteflag
    1
    ;; uint8 _externflag
    1
    ;; uint8 _datalen
    1
    ;; uint8[8] _data
    (* 1    8)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32 _id
       (write-long _id s)
     ;; uint32 _timeflag
       (write-long _timeflag s)
     ;; uint8 _sendtype
       (write-byte _sendtype s)
     ;; uint8 _remoteflag
       (write-byte _remoteflag s)
     ;; uint8 _externflag
       (write-byte _externflag s)
     ;; uint8 _datalen
       (write-byte _datalen s)
     ;; uint8[8] _data
     (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32 _id
     (setq _id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _timeflag
     (setq _timeflag (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _sendtype
     (setq _sendtype (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _remoteflag
     (setq _remoteflag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _externflag
     (setq _externflag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _datalen
     (setq _datalen (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8[8] _data
   (setq _data (make-array 8 :element-type :char))
   (replace _data buf :start2 ptr-) (incf ptr- 8)
   ;;
   self)
  )

(setf (get canalystii_node_msg::can :md5sum-) "e974a5e243febe68ac8618d673926338")
(setf (get canalystii_node_msg::can :datatype-) "canalystii_node_msg/can")
(setf (get canalystii_node_msg::can :definition-)
      "Header header
uint32 id
uint32 timeflag
uint8 sendtype
uint8 remoteflag
uint8 externflag
uint8 datalen
uint8[8] data

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :canalystii_node_msg/can "e974a5e243febe68ac8618d673926338")


