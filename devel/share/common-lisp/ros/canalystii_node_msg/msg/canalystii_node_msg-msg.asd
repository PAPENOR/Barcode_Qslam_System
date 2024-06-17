
(cl:in-package :asdf)

(defsystem "canalystii_node_msg-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "can" :depends-on ("_package_can"))
    (:file "_package_can" :depends-on ("_package"))
  ))