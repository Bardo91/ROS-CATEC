"""autogenerated by genpy from catec_msgs/AALState.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg

class AALState(genpy.Message):
  _md5sum = "e82adcfa3a988ed0f95e35f8be72eb44"
  _type = "catec_msgs/AALState"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint8 CONTRACTED=1
uint8 CONTRACTING=1
uint8 EXTENDED=1
uint8 EXTENDING=1
uint8 state
Position final_effector_position
Orientation final_effector_orientation
float64    claw
float64[6] joints_angles



================================================================================
MSG: catec_msgs/Position
float64 x
float64 y
float64 z
================================================================================
MSG: catec_msgs/Orientation
float64 x
float64 y
float64 z
"""
  # Pseudo-constants
  CONTRACTED = 1
  CONTRACTING = 1
  EXTENDED = 1
  EXTENDING = 1

  __slots__ = ['state','final_effector_position','final_effector_orientation','claw','joints_angles']
  _slot_types = ['uint8','catec_msgs/Position','catec_msgs/Orientation','float64','float64[6]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       state,final_effector_position,final_effector_orientation,claw,joints_angles

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(AALState, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.state is None:
        self.state = 0
      if self.final_effector_position is None:
        self.final_effector_position = catec_msgs.msg.Position()
      if self.final_effector_orientation is None:
        self.final_effector_orientation = catec_msgs.msg.Orientation()
      if self.claw is None:
        self.claw = 0.
      if self.joints_angles is None:
        self.joints_angles = [0.,0.,0.,0.,0.,0.]
    else:
      self.state = 0
      self.final_effector_position = catec_msgs.msg.Position()
      self.final_effector_orientation = catec_msgs.msg.Orientation()
      self.claw = 0.
      self.joints_angles = [0.,0.,0.,0.,0.,0.]

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
      buff.write(_struct_B7d.pack(_x.state, _x.final_effector_position.x, _x.final_effector_position.y, _x.final_effector_position.z, _x.final_effector_orientation.x, _x.final_effector_orientation.y, _x.final_effector_orientation.z, _x.claw))
      buff.write(_struct_6d.pack(*self.joints_angles))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.final_effector_position is None:
        self.final_effector_position = catec_msgs.msg.Position()
      if self.final_effector_orientation is None:
        self.final_effector_orientation = catec_msgs.msg.Orientation()
      end = 0
      _x = self
      start = end
      end += 57
      (_x.state, _x.final_effector_position.x, _x.final_effector_position.y, _x.final_effector_position.z, _x.final_effector_orientation.x, _x.final_effector_orientation.y, _x.final_effector_orientation.z, _x.claw,) = _struct_B7d.unpack(str[start:end])
      start = end
      end += 48
      self.joints_angles = _struct_6d.unpack(str[start:end])
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
      buff.write(_struct_B7d.pack(_x.state, _x.final_effector_position.x, _x.final_effector_position.y, _x.final_effector_position.z, _x.final_effector_orientation.x, _x.final_effector_orientation.y, _x.final_effector_orientation.z, _x.claw))
      buff.write(self.joints_angles.tostring())
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.final_effector_position is None:
        self.final_effector_position = catec_msgs.msg.Position()
      if self.final_effector_orientation is None:
        self.final_effector_orientation = catec_msgs.msg.Orientation()
      end = 0
      _x = self
      start = end
      end += 57
      (_x.state, _x.final_effector_position.x, _x.final_effector_position.y, _x.final_effector_position.z, _x.final_effector_orientation.x, _x.final_effector_orientation.y, _x.final_effector_orientation.z, _x.claw,) = _struct_B7d.unpack(str[start:end])
      start = end
      end += 48
      self.joints_angles = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=6)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_6d = struct.Struct("<6d")
_struct_B7d = struct.Struct("<B7d")
