
(cl:in-package :asdf)

(defsystem "rbx2_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetBatteryLevel" :depends-on ("_package_SetBatteryLevel"))
    (:file "_package_SetBatteryLevel" :depends-on ("_package"))
  ))