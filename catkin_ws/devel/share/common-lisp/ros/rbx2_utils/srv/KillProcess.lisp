; Auto-generated. Do not edit!


(cl:in-package rbx2_utils-srv)


;//! \htmlinclude KillProcess-request.msg.html

(cl:defclass <KillProcess-request> (roslisp-msg-protocol:ros-message)
  ((process_id
    :reader process_id
    :initarg :process_id
    :type cl:string
    :initform ""))
)

(cl:defclass KillProcess-request (<KillProcess-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KillProcess-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KillProcess-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_utils-srv:<KillProcess-request> is deprecated: use rbx2_utils-srv:KillProcess-request instead.")))

(cl:ensure-generic-function 'process_id-val :lambda-list '(m))
(cl:defmethod process_id-val ((m <KillProcess-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbx2_utils-srv:process_id-val is deprecated.  Use rbx2_utils-srv:process_id instead.")
  (process_id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KillProcess-request>) ostream)
  "Serializes a message object of type '<KillProcess-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'process_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'process_id))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KillProcess-request>) istream)
  "Deserializes a message object of type '<KillProcess-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'process_id) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'process_id) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KillProcess-request>)))
  "Returns string type for a service object of type '<KillProcess-request>"
  "rbx2_utils/KillProcessRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KillProcess-request)))
  "Returns string type for a service object of type 'KillProcess-request"
  "rbx2_utils/KillProcessRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KillProcess-request>)))
  "Returns md5sum for a message object of type '<KillProcess-request>"
  "54319f819462371f5e2b56e424d9b26f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KillProcess-request)))
  "Returns md5sum for a message object of type 'KillProcess-request"
  "54319f819462371f5e2b56e424d9b26f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KillProcess-request>)))
  "Returns full string definition for message of type '<KillProcess-request>"
  (cl:format cl:nil "string process_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KillProcess-request)))
  "Returns full string definition for message of type 'KillProcess-request"
  (cl:format cl:nil "string process_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KillProcess-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'process_id))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KillProcess-request>))
  "Converts a ROS message object to a list"
  (cl:list 'KillProcess-request
    (cl:cons ':process_id (process_id msg))
))
;//! \htmlinclude KillProcess-response.msg.html

(cl:defclass <KillProcess-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass KillProcess-response (<KillProcess-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <KillProcess-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'KillProcess-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_utils-srv:<KillProcess-response> is deprecated: use rbx2_utils-srv:KillProcess-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <KillProcess-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbx2_utils-srv:success-val is deprecated.  Use rbx2_utils-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <KillProcess-response>) ostream)
  "Serializes a message object of type '<KillProcess-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <KillProcess-response>) istream)
  "Deserializes a message object of type '<KillProcess-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<KillProcess-response>)))
  "Returns string type for a service object of type '<KillProcess-response>"
  "rbx2_utils/KillProcessResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KillProcess-response)))
  "Returns string type for a service object of type 'KillProcess-response"
  "rbx2_utils/KillProcessResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<KillProcess-response>)))
  "Returns md5sum for a message object of type '<KillProcess-response>"
  "54319f819462371f5e2b56e424d9b26f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'KillProcess-response)))
  "Returns md5sum for a message object of type 'KillProcess-response"
  "54319f819462371f5e2b56e424d9b26f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<KillProcess-response>)))
  "Returns full string definition for message of type '<KillProcess-response>"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'KillProcess-response)))
  "Returns full string definition for message of type 'KillProcess-response"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <KillProcess-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <KillProcess-response>))
  "Converts a ROS message object to a list"
  (cl:list 'KillProcess-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'KillProcess)))
  'KillProcess-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'KillProcess)))
  'KillProcess-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'KillProcess)))
  "Returns string type for a service object of type '<KillProcess>"
  "rbx2_utils/KillProcess")