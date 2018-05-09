; Auto-generated. Do not edit!


(cl:in-package rbx2_utils-srv)


;//! \htmlinclude LaunchProcess-request.msg.html

(cl:defclass <LaunchProcess-request> (roslisp-msg-protocol:ros-message)
  ((command
    :reader command
    :initarg :command
    :type cl:string
    :initform ""))
)

(cl:defclass LaunchProcess-request (<LaunchProcess-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LaunchProcess-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LaunchProcess-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_utils-srv:<LaunchProcess-request> is deprecated: use rbx2_utils-srv:LaunchProcess-request instead.")))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <LaunchProcess-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbx2_utils-srv:command-val is deprecated.  Use rbx2_utils-srv:command instead.")
  (command m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LaunchProcess-request>) ostream)
  "Serializes a message object of type '<LaunchProcess-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'command))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'command))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LaunchProcess-request>) istream)
  "Deserializes a message object of type '<LaunchProcess-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'command) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LaunchProcess-request>)))
  "Returns string type for a service object of type '<LaunchProcess-request>"
  "rbx2_utils/LaunchProcessRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LaunchProcess-request)))
  "Returns string type for a service object of type 'LaunchProcess-request"
  "rbx2_utils/LaunchProcessRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LaunchProcess-request>)))
  "Returns md5sum for a message object of type '<LaunchProcess-request>"
  "15f55f5751b44d06bcad0321b1a88466")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LaunchProcess-request)))
  "Returns md5sum for a message object of type 'LaunchProcess-request"
  "15f55f5751b44d06bcad0321b1a88466")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LaunchProcess-request>)))
  "Returns full string definition for message of type '<LaunchProcess-request>"
  (cl:format cl:nil "string command~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LaunchProcess-request)))
  "Returns full string definition for message of type 'LaunchProcess-request"
  (cl:format cl:nil "string command~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LaunchProcess-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'command))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LaunchProcess-request>))
  "Converts a ROS message object to a list"
  (cl:list 'LaunchProcess-request
    (cl:cons ':command (command msg))
))
;//! \htmlinclude LaunchProcess-response.msg.html

(cl:defclass <LaunchProcess-response> (roslisp-msg-protocol:ros-message)
  ((process_id
    :reader process_id
    :initarg :process_id
    :type cl:string
    :initform ""))
)

(cl:defclass LaunchProcess-response (<LaunchProcess-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LaunchProcess-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LaunchProcess-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbx2_utils-srv:<LaunchProcess-response> is deprecated: use rbx2_utils-srv:LaunchProcess-response instead.")))

(cl:ensure-generic-function 'process_id-val :lambda-list '(m))
(cl:defmethod process_id-val ((m <LaunchProcess-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbx2_utils-srv:process_id-val is deprecated.  Use rbx2_utils-srv:process_id instead.")
  (process_id m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LaunchProcess-response>) ostream)
  "Serializes a message object of type '<LaunchProcess-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'process_id))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'process_id))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LaunchProcess-response>) istream)
  "Deserializes a message object of type '<LaunchProcess-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LaunchProcess-response>)))
  "Returns string type for a service object of type '<LaunchProcess-response>"
  "rbx2_utils/LaunchProcessResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LaunchProcess-response)))
  "Returns string type for a service object of type 'LaunchProcess-response"
  "rbx2_utils/LaunchProcessResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LaunchProcess-response>)))
  "Returns md5sum for a message object of type '<LaunchProcess-response>"
  "15f55f5751b44d06bcad0321b1a88466")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LaunchProcess-response)))
  "Returns md5sum for a message object of type 'LaunchProcess-response"
  "15f55f5751b44d06bcad0321b1a88466")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LaunchProcess-response>)))
  "Returns full string definition for message of type '<LaunchProcess-response>"
  (cl:format cl:nil "string process_id~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LaunchProcess-response)))
  "Returns full string definition for message of type 'LaunchProcess-response"
  (cl:format cl:nil "string process_id~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LaunchProcess-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'process_id))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LaunchProcess-response>))
  "Converts a ROS message object to a list"
  (cl:list 'LaunchProcess-response
    (cl:cons ':process_id (process_id msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'LaunchProcess)))
  'LaunchProcess-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'LaunchProcess)))
  'LaunchProcess-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LaunchProcess)))
  "Returns string type for a service object of type '<LaunchProcess>"
  "rbx2_utils/LaunchProcess")