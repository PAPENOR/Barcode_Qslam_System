// Auto-generated. Do not edit!

// (in-package canalystii_node_msg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class can {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.id = null;
      this.timeflag = null;
      this.sendtype = null;
      this.remoteflag = null;
      this.externflag = null;
      this.datalen = null;
      this.data = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('timeflag')) {
        this.timeflag = initObj.timeflag
      }
      else {
        this.timeflag = 0;
      }
      if (initObj.hasOwnProperty('sendtype')) {
        this.sendtype = initObj.sendtype
      }
      else {
        this.sendtype = 0;
      }
      if (initObj.hasOwnProperty('remoteflag')) {
        this.remoteflag = initObj.remoteflag
      }
      else {
        this.remoteflag = 0;
      }
      if (initObj.hasOwnProperty('externflag')) {
        this.externflag = initObj.externflag
      }
      else {
        this.externflag = 0;
      }
      if (initObj.hasOwnProperty('datalen')) {
        this.datalen = initObj.datalen
      }
      else {
        this.datalen = 0;
      }
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = new Array(8).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type can
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [id]
    bufferOffset = _serializer.uint32(obj.id, buffer, bufferOffset);
    // Serialize message field [timeflag]
    bufferOffset = _serializer.uint32(obj.timeflag, buffer, bufferOffset);
    // Serialize message field [sendtype]
    bufferOffset = _serializer.uint8(obj.sendtype, buffer, bufferOffset);
    // Serialize message field [remoteflag]
    bufferOffset = _serializer.uint8(obj.remoteflag, buffer, bufferOffset);
    // Serialize message field [externflag]
    bufferOffset = _serializer.uint8(obj.externflag, buffer, bufferOffset);
    // Serialize message field [datalen]
    bufferOffset = _serializer.uint8(obj.datalen, buffer, bufferOffset);
    // Check that the constant length array field [data] has the right length
    if (obj.data.length !== 8) {
      throw new Error('Unable to serialize array field data - length must be 8')
    }
    // Serialize message field [data]
    bufferOffset = _arraySerializer.uint8(obj.data, buffer, bufferOffset, 8);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type can
    let len;
    let data = new can(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [id]
    data.id = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [timeflag]
    data.timeflag = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [sendtype]
    data.sendtype = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [remoteflag]
    data.remoteflag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [externflag]
    data.externflag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [datalen]
    data.datalen = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [data]
    data.data = _arrayDeserializer.uint8(buffer, bufferOffset, 8)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'canalystii_node_msg/can';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e974a5e243febe68ac8618d673926338';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new can(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.timeflag !== undefined) {
      resolved.timeflag = msg.timeflag;
    }
    else {
      resolved.timeflag = 0
    }

    if (msg.sendtype !== undefined) {
      resolved.sendtype = msg.sendtype;
    }
    else {
      resolved.sendtype = 0
    }

    if (msg.remoteflag !== undefined) {
      resolved.remoteflag = msg.remoteflag;
    }
    else {
      resolved.remoteflag = 0
    }

    if (msg.externflag !== undefined) {
      resolved.externflag = msg.externflag;
    }
    else {
      resolved.externflag = 0
    }

    if (msg.datalen !== undefined) {
      resolved.datalen = msg.datalen;
    }
    else {
      resolved.datalen = 0
    }

    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = new Array(8).fill(0)
    }

    return resolved;
    }
};

module.exports = can;
