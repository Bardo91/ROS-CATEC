"""autogenerated by genpy from catec_msgs/UALStateStamped.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg
import std_msgs.msg

class UALStateStamped(genpy.Message):
  _md5sum = "62ad5d37efcfa778426c3363b391032d"
  _type = "catec_msgs/UALStateStamped"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
UALState ual_state
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.secs: seconds (stamp_secs) since epoch
# * stamp.nsecs: nanoseconds since stamp_secs
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: catec_msgs/UALState
DynamicState dynamic_state
uint8 flying_state
uint8 remaining_battery
uint8 memory_usage
uint8 cpu_usage
================================================================================
MSG: catec_msgs/DynamicState
PositionWithCheck position
OrientationWithCheck orientation
VelocityWithCheck velocity
================================================================================
MSG: catec_msgs/PositionWithCheck
float64 x
float64 y
float64 z
uint8 valid
================================================================================
MSG: catec_msgs/OrientationWithCheck
float64 x
float64 y
float64 z
uint8 valid
================================================================================
MSG: catec_msgs/VelocityWithCheck
float64 x
float64 y
float64 z
uint8 valid
"""
  __slots__ = ['header','ual_state']
  _slot_types = ['std_msgs/Header','catec_msgs/UALState']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,ual_state

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(UALStateStamped, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.ual_state is None:
        self.ual_state = catec_msgs.msg.UALState()
    else:
      self.header = std_msgs.msg.Header()
      self.ual_state = catec_msgs.msg.UALState()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3dB3dB3d5B.pack(_x.ual_state.dynamic_state.position.x, _x.ual_state.dynamic_state.position.y, _x.ual_state.dynamic_state.position.z, _x.ual_state.dynamic_state.position.valid, _x.ual_state.dynamic_state.orientation.x, _x.ual_state.dynamic_state.orientation.y, _x.ual_state.dynamic_state.orientation.z, _x.ual_state.dynamic_state.orientation.valid, _x.ual_state.dynamic_state.velocity.x, _x.ual_state.dynamic_state.velocity.y, _x.ual_state.dynamic_state.velocity.z, _x.ual_state.dynamic_state.velocity.valid, _x.ual_state.flying_state, _x.ual_state.remaining_battery, _x.ual_state.memory_usage, _x.ual_state.cpu_usage))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.ual_state is None:
        self.ual_state = catec_msgs.msg.UALState()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 79
      (_x.ual_state.dynamic_state.position.x, _x.ual_state.dynamic_state.position.y, _x.ual_state.dynamic_state.position.z, _x.ual_state.dynamic_state.position.valid, _x.ual_state.dynamic_state.orientation.x, _x.ual_state.dynamic_state.orientation.y, _x.ual_state.dynamic_state.orientation.z, _x.ual_state.dynamic_state.orientation.valid, _x.ual_state.dynamic_state.velocity.x, _x.ual_state.dynamic_state.velocity.y, _x.ual_state.dynamic_state.velocity.z, _x.ual_state.dynamic_state.velocity.valid, _x.ual_state.flying_state, _x.ual_state.remaining_battery, _x.ual_state.memory_usage, _x.ual_state.cpu_usage,) = _struct_3dB3dB3d5B.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3dB3dB3d5B.pack(_x.ual_state.dynamic_state.position.x, _x.ual_state.dynamic_state.position.y, _x.ual_state.dynamic_state.position.z, _x.ual_state.dynamic_state.position.valid, _x.ual_state.dynamic_state.orientation.x, _x.ual_state.dynamic_state.orientation.y, _x.ual_state.dynamic_state.orientation.z, _x.ual_state.dynamic_state.orientation.valid, _x.ual_state.dynamic_state.velocity.x, _x.ual_state.dynamic_state.velocity.y, _x.ual_state.dynamic_state.velocity.z, _x.ual_state.dynamic_state.velocity.valid, _x.ual_state.flying_state, _x.ual_state.remaining_battery, _x.ual_state.memory_usage, _x.ual_state.cpu_usage))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.ual_state is None:
        self.ual_state = catec_msgs.msg.UALState()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 79
      (_x.ual_state.dynamic_state.position.x, _x.ual_state.dynamic_state.position.y, _x.ual_state.dynamic_state.position.z, _x.ual_state.dynamic_state.position.valid, _x.ual_state.dynamic_state.orientation.x, _x.ual_state.dynamic_state.orientation.y, _x.ual_state.dynamic_state.orientation.z, _x.ual_state.dynamic_state.orientation.valid, _x.ual_state.dynamic_state.velocity.x, _x.ual_state.dynamic_state.velocity.y, _x.ual_state.dynamic_state.velocity.z, _x.ual_state.dynamic_state.velocity.valid, _x.ual_state.flying_state, _x.ual_state.remaining_battery, _x.ual_state.memory_usage, _x.ual_state.cpu_usage,) = _struct_3dB3dB3d5B.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3I = struct.Struct("<3I")
_struct_3dB3dB3d5B = struct.Struct("<3dB3dB3d5B")
