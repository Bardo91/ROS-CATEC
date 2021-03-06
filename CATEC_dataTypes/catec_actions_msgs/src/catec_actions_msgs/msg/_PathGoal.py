"""autogenerated by genpy from catec_actions_msgs/PathGoal.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg

class PathGoal(genpy.Message):
  _md5sum = "987187562942dbd0b5b93849ed4a5345"
  _type = "catec_actions_msgs/PathGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
catec_msgs/Position initial_position
catec_msgs/Position final_position

================================================================================
MSG: catec_msgs/Position
float64 x
float64 y
float64 z
"""
  __slots__ = ['initial_position','final_position']
  _slot_types = ['catec_msgs/Position','catec_msgs/Position']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       initial_position,final_position

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(PathGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.initial_position is None:
        self.initial_position = catec_msgs.msg.Position()
      if self.final_position is None:
        self.final_position = catec_msgs.msg.Position()
    else:
      self.initial_position = catec_msgs.msg.Position()
      self.final_position = catec_msgs.msg.Position()

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
      buff.write(_struct_6d.pack(_x.initial_position.x, _x.initial_position.y, _x.initial_position.z, _x.final_position.x, _x.final_position.y, _x.final_position.z))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.initial_position is None:
        self.initial_position = catec_msgs.msg.Position()
      if self.final_position is None:
        self.final_position = catec_msgs.msg.Position()
      end = 0
      _x = self
      start = end
      end += 48
      (_x.initial_position.x, _x.initial_position.y, _x.initial_position.z, _x.final_position.x, _x.final_position.y, _x.final_position.z,) = _struct_6d.unpack(str[start:end])
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
      buff.write(_struct_6d.pack(_x.initial_position.x, _x.initial_position.y, _x.initial_position.z, _x.final_position.x, _x.final_position.y, _x.final_position.z))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.initial_position is None:
        self.initial_position = catec_msgs.msg.Position()
      if self.final_position is None:
        self.final_position = catec_msgs.msg.Position()
      end = 0
      _x = self
      start = end
      end += 48
      (_x.initial_position.x, _x.initial_position.y, _x.initial_position.z, _x.final_position.x, _x.final_position.y, _x.final_position.z,) = _struct_6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_6d = struct.Struct("<6d")
