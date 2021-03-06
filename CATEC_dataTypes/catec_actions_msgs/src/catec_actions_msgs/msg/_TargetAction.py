"""autogenerated by genpy from catec_actions_msgs/TargetAction.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_actions_msgs.msg
import catec_msgs.msg
import genpy
import actionlib_msgs.msg
import std_msgs.msg

class TargetAction(genpy.Message):
  _md5sum = "687480231ad800cdef4e2fffdf7127e4"
  _type = "catec_actions_msgs/TargetAction"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

TargetActionGoal action_goal
TargetActionResult action_result
TargetActionFeedback action_feedback

================================================================================
MSG: catec_actions_msgs/TargetActionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalID goal_id
TargetGoal goal

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
MSG: actionlib_msgs/GoalID
# The stamp should store the time at which this goal was requested.
# It is used by an action server when it tries to preempt all
# goals that were requested before a certain time
time stamp

# The id provides a way to associate feedback and
# result message with specific goal requests. The id
# specified must be unique.
string id


================================================================================
MSG: catec_actions_msgs/TargetGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
uint8 target_type

================================================================================
MSG: catec_actions_msgs/TargetActionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
TargetResult result

================================================================================
MSG: actionlib_msgs/GoalStatus
GoalID goal_id
uint8 status
uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server

#Allow for the user to associate a string with GoalStatus for debugging
string text


================================================================================
MSG: catec_actions_msgs/TargetResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#result definition
catec_msgs/TargetsDetectedStamped targets

================================================================================
MSG: catec_msgs/TargetsDetectedStamped
Header header
TargetsDetected targets
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
================================================================================
MSG: catec_actions_msgs/TargetActionFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
TargetFeedback feedback

================================================================================
MSG: catec_actions_msgs/TargetFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#feedback definition
catec_msgs/TargetsDetectedStamped targets

"""
  __slots__ = ['action_goal','action_result','action_feedback']
  _slot_types = ['catec_actions_msgs/TargetActionGoal','catec_actions_msgs/TargetActionResult','catec_actions_msgs/TargetActionFeedback']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       action_goal,action_result,action_feedback

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TargetAction, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.action_goal is None:
        self.action_goal = catec_actions_msgs.msg.TargetActionGoal()
      if self.action_result is None:
        self.action_result = catec_actions_msgs.msg.TargetActionResult()
      if self.action_feedback is None:
        self.action_feedback = catec_actions_msgs.msg.TargetActionFeedback()
    else:
      self.action_goal = catec_actions_msgs.msg.TargetActionGoal()
      self.action_result = catec_actions_msgs.msg.TargetActionResult()
      self.action_feedback = catec_actions_msgs.msg.TargetActionFeedback()

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
      buff.write(_struct_3I.pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_B3I.pack(_x.action_goal.goal.target_type, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I.pack(_x.action_result.result.targets.header.seq, _x.action_result.result.targets.header.stamp.secs, _x.action_result.result.targets.header.stamp.nsecs))
      _x = self.action_result.result.targets.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.action_result.result.targets.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.action_result.result.targets.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v1 = val1.position
        _x = _v1
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      _x = self
      buff.write(_struct_4I.pack(_x.action_result.result.targets.targets.size, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I.pack(_x.action_feedback.feedback.targets.header.seq, _x.action_feedback.feedback.targets.header.stamp.secs, _x.action_feedback.feedback.targets.header.stamp.nsecs))
      _x = self.action_feedback.feedback.targets.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.action_feedback.feedback.targets.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.action_feedback.feedback.targets.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v2 = val1.position
        _x = _v2
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      buff.write(_struct_I.pack(self.action_feedback.feedback.targets.targets.size))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.action_goal is None:
        self.action_goal = catec_actions_msgs.msg.TargetActionGoal()
      if self.action_result is None:
        self.action_result = catec_actions_msgs.msg.TargetActionResult()
      if self.action_feedback is None:
        self.action_feedback = catec_actions_msgs.msg.TargetActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 13
      (_x.action_goal.goal.target_type, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _struct_B3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _struct_B.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_result.result.targets.header.seq, _x.action_result.result.targets.header.stamp.secs, _x.action_result.result.targets.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.result.targets.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.result.targets.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.action_result.result.targets.targets.targets = []
      for i in range(0, length):
        val1 = catec_msgs.msg.Target()
        start = end
        end += 1
        (val1.target,) = _struct_B.unpack(str[start:end])
        _v3 = val1.position
        _x = _v3
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.action_result.result.targets.targets.targets.append(val1)
      _x = self
      start = end
      end += 16
      (_x.action_result.result.targets.targets.size, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _struct_4I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _struct_B.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_feedback.feedback.targets.header.seq, _x.action_feedback.feedback.targets.header.stamp.secs, _x.action_feedback.feedback.targets.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.feedback.targets.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.feedback.targets.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.action_feedback.feedback.targets.targets.targets = []
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
        self.action_feedback.feedback.targets.targets.targets.append(val1)
      start = end
      end += 4
      (self.action_feedback.feedback.targets.targets.size,) = _struct_I.unpack(str[start:end])
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
      buff.write(_struct_3I.pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_B3I.pack(_x.action_goal.goal.target_type, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I.pack(_x.action_result.result.targets.header.seq, _x.action_result.result.targets.header.stamp.secs, _x.action_result.result.targets.header.stamp.nsecs))
      _x = self.action_result.result.targets.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.action_result.result.targets.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.action_result.result.targets.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v5 = val1.position
        _x = _v5
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      _x = self
      buff.write(_struct_4I.pack(_x.action_result.result.targets.targets.size, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2I.pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_3I.pack(_x.action_feedback.feedback.targets.header.seq, _x.action_feedback.feedback.targets.header.stamp.secs, _x.action_feedback.feedback.targets.header.stamp.nsecs))
      _x = self.action_feedback.feedback.targets.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.action_feedback.feedback.targets.targets.targets)
      buff.write(_struct_I.pack(length))
      for val1 in self.action_feedback.feedback.targets.targets.targets:
        buff.write(_struct_B.pack(val1.target))
        _v6 = val1.position
        _x = _v6
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
      buff.write(_struct_I.pack(self.action_feedback.feedback.targets.targets.size))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.action_goal is None:
        self.action_goal = catec_actions_msgs.msg.TargetActionGoal()
      if self.action_result is None:
        self.action_result = catec_actions_msgs.msg.TargetActionResult()
      if self.action_feedback is None:
        self.action_feedback = catec_actions_msgs.msg.TargetActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 13
      (_x.action_goal.goal.target_type, _x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _struct_B3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _struct_B.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_result.result.targets.header.seq, _x.action_result.result.targets.header.stamp.secs, _x.action_result.result.targets.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.result.targets.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.result.targets.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.action_result.result.targets.targets.targets = []
      for i in range(0, length):
        val1 = catec_msgs.msg.Target()
        start = end
        end += 1
        (val1.target,) = _struct_B.unpack(str[start:end])
        _v7 = val1.position
        _x = _v7
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.action_result.result.targets.targets.targets.append(val1)
      _x = self
      start = end
      end += 16
      (_x.action_result.result.targets.targets.size, _x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _struct_4I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _struct_2I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _struct_B.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_feedback.feedback.targets.header.seq, _x.action_feedback.feedback.targets.header.stamp.secs, _x.action_feedback.feedback.targets.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.feedback.targets.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.feedback.targets.header.frame_id = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.action_feedback.feedback.targets.targets.targets = []
      for i in range(0, length):
        val1 = catec_msgs.msg.Target()
        start = end
        end += 1
        (val1.target,) = _struct_B.unpack(str[start:end])
        _v8 = val1.position
        _x = _v8
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        self.action_feedback.feedback.targets.targets.targets.append(val1)
      start = end
      end += 4
      (self.action_feedback.feedback.targets.targets.size,) = _struct_I.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_B = struct.Struct("<B")
_struct_3I = struct.Struct("<3I")
_struct_B3I = struct.Struct("<B3I")
_struct_4I = struct.Struct("<4I")
_struct_2I = struct.Struct("<2I")
_struct_3d = struct.Struct("<3d")
