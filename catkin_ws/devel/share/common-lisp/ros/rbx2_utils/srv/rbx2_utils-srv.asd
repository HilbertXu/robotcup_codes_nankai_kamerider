
(cl:in-package :asdf)

(defsystem "rbx2_utils-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "KillProcess" :depends-on ("_package_KillProcess"))
    (:file "_package_KillProcess" :depends-on ("_package"))
    (:file "OldLaunchProcess" :depends-on ("_package_OldLaunchProcess"))
    (:file "_package_OldLaunchProcess" :depends-on ("_package"))
    (:file "LaunchProcess" :depends-on ("_package_LaunchProcess"))
    (:file "_package_LaunchProcess" :depends-on ("_package"))
  ))