"""autogenerated by genpy from catec_msgs/TargetsDetectedStamped.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg
import std_msgs.msg

class TargetsDetectedStamped(genpy.Message):
  _md5sum = "4eec53625663b400eb2a57857361a4c2"
  _type = "catec_msgs/TargetsDetectedStamped"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
TargetsDetected targets
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
MSG: catec_msgs/TargetsDetected
Target[] targets
uint32 size
================================================================================
MSG: catec_msgs/Target
uint8 BOTH=0
uint8 FIRST=1
uint8 SECOND=2
uint8 target
Position position
================================================================================
MSG: catec_msgs/Position
float64 x
float64 y
float64 z
"""
  __slots__ = ['header','targets']
  _slot_types = ['std_msgs/Header','catec_msgs/TargetsDetected']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,targets

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TargetsDetectedStamped, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.targets is None:
        self.targets = catec_msgs.msg.TargetsDetected()
    else:
      self.header = std_msgs.msg.Header()
      self.targets = catec_msgs.msg.TargetsDetected()

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
      length = len(self.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v1 = val1.position
        _x = _v1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      buff.write(_struct_I.pack(self.targets.size))
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
      if self.targets is None:
        self.targets = catec_msgs.msg.TargetsDetected()
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
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.targets.targets = []
      for i in range(0, length):
        val1 = catec_msgs.msg.Target()
        start = end
        end += 1
        (val1.target,) = _struct_B.unpack(str[start:end])
        _v2 = val1.position
        _x = _v2
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.targets.targets.append(val1)
      start = end
      end += 4
      (self.targets.size,) = _struct_I.unpack(str[start:end])
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
      length = len(self.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v3 = val1.position
        _x = _v3
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      buff.write(_struct_I.pack(self.targets.size))
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
      if self.targets is None:
        self.targets = catec_msgs.msg.TargetsDetected()
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
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.targets.targets = []
      for i in range(0, length):
        val1 = catec_msgs.msg.Target()
        start = end
        end += 1
        (val1.target,) = _struct_B.unpack(str[start:end])
        _v4 = val1.position
        _x = _v4
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.targets.targets.append(val1)
      start = end
      end += 4
      (self.targets.size,) = _struct_I.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3I = struct.Struct("<3I")
_struct_B = struct.Struct("<B")
_struct_3d = struct.Struct("<3d")
