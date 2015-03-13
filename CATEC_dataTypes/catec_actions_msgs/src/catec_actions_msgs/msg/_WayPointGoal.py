"""autogenerated by genpy from catec_actions_msgs/WayPointGoal.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg

class WayPointGoal(genpy.Message):
  _md5sum = "f8dce9f5261654fa8a8325e1cba7b8f4"
  _type = "catec_actions_msgs/WayPointGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
catec_msgs/WayPointWithCruise waypoint

================================================================================
MSG: catec_msgs/WayPointWithCruise
float64 x
float64 y
float64 z
float32 cruise
float64 heading
"""
  __slots__ = ['waypoint']
  _slot_types = ['catec_msgs/WayPointWithCruise']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       waypoint

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(WayPointGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.waypoint is None:
        self.waypoint = catec_msgs.msg.WayPointWithCruise()
    else:
      self.waypoint = catec_msgs.msg.WayPointWithCruise()

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
      buff.write(_struct_3dfd.pack(_x.waypoint.x, _x.waypoint.y, _x.waypoint.z, _x.waypoint.cruise, _x.waypoint.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.waypoint is None:
        self.waypoint = catec_msgs.msg.WayPointWithCruise()
      end = 0
      _x = self
      start = end
      end += 36
      (_x.waypoint.x, _x.waypoint.y, _x.waypoint.z, _x.waypoint.cruise, _x.waypoint.heading,) = _struct_3dfd.unpack(str[start:end])
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
      buff.write(_struct_3dfd.pack(_x.waypoint.x, _x.waypoint.y, _x.waypoint.z, _x.waypoint.cruise, _x.waypoint.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.waypoint is None:
        self.waypoint = catec_msgs.msg.WayPointWithCruise()
      end = 0
      _x = self
      start = end
      end += 36
      (_x.waypoint.x, _x.waypoint.y, _x.waypoint.z, _x.waypoint.cruise, _x.waypoint.heading,) = _struct_3dfd.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3dfd = struct.Struct("<3dfd")
