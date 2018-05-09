; Auto-generated. Do not edit!


(cl:in-package rbx2_msgs-srv)


;//! \htmlinclude SetBatteryLevel-request.msg.html

(cl:defclass <SetBatteryLevel-request> (roslisp-msg-protocol:ros-message)
  ((value
    :reader value
    :initarg :value
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetBatteryLevel-request (<SetBatteryLevel-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetBatteryLevel-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetBatteryLevel-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_msgs-srv:<SetBatteryLevel-request> is deprecated: use rbx2_msgs-srv:SetBatteryLevel-request instead.")))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <SetBatteryLevel-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbx2_msgs-srv:value-val is deprecated.  Use rbx2_msgs-srv:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetBatteryLevel-request>) ostream)
  "Serializes a message object of type '<SetBatteryLevel-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetBatteryLevel-request>) istream)
  "Deserializes a message object of type '<SetBatteryLevel-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'value) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetBatteryLevel-request>)))
  "Returns string type for a service object of type '<SetBatteryLevel-request>"
  "rbx2_msgs/SetBatteryLevelRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetBatteryLevel-request)))
  "Returns string type for a service object of type 'SetBatteryLevel-request"
  "rbx2_msgs/SetBatteryLevelRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetBatteryLevel-request>)))
  "Returns md5sum for a message object of type '<SetBatteryLevel-request>"
  "0aca93dcf6d857f0e5a0dc6be1eaa9fb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetBatteryLevel-request)))
  "Returns md5sum for a message object of type 'SetBatteryLevel-request"
  "0aca93dcf6d857f0e5a0dc6be1eaa9fb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetBatteryLevel-request>)))
  "Returns full string definition for message of type '<SetBatteryLevel-request>"
  (cl:format cl:nil "float32 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetBatteryLevel-request)))
  "Returns full string definition for message of type 'SetBatteryLevel-request"
  (cl:format cl:nil "float32 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetBatteryLevel-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetBatteryLevel-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetBatteryLevel-request
    (cl:cons ':value (value msg))
))
;//! \htmlinclude SetBatteryLevel-response.msg.html

(cl:defclass <SetBatteryLevel-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetBatteryLevel-response (<SetBatteryLevel-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetBatteryLevel-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetBatteryLevel-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_msgs-srv:<SetBatteryLevel-response> is deprecated: use rbx2_msgs-srv:SetBatteryLevel-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetBatteryLevel-response>) ostream)
  "Serializes a message object of type '<SetBatteryLevel-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetBatteryLevel-response>) istream)
  "Deserializes a message object of type '<SetBatteryLevel-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetBatteryLevel-response>)))
  "Returns string type for a service object of type '<SetBatteryLevel-response>"
  "rbx2_msgs/SetBatteryLevelResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetBatteryLevel-response)))
  "Returns string type for a service object of type 'SetBatteryLevel-response"
  "rbx2_msgs/SetBatteryLevelResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetBatteryLevel-response>)))
  "Returns md5sum for a message object of type '<SetBatteryLevel-response>"
  "0aca93dcf6d857f0e5a0dc6be1eaa9fb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetBatteryLevel-response)))
  "Returns md5sum for a message object of type 'SetBatteryLevel-response"
  "0aca93dcf6d857f0e5a0dc6be1eaa9fb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetBatteryLevel-response>)))
  "Returns full string definition for message of type '<SetBatteryLevel-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetBatteryLevel-response)))
  "Returns full string definition for message of type 'SetBatteryLevel-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetBatteryLevel-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetBatteryLevel-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetBatteryLevel-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetBatteryLevel)))
  'SetBatteryLevel-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetBatteryLevel)))
  'SetBatteryLevel-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetBatteryLevel)))
  "Returns string type for a service object of type '<SetBatteryLevel>"
  "rbx2_msgs/SetBatteryLevel")