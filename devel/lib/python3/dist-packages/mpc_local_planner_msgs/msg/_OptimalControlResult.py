# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from mpc_local_planner_msgs/OptimalControlResult.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import std_msgs.msg

class OptimalControlResult(genpy.Message):
  _md5sum = "43eac4f3a65752bab175326ddc347c3d"
  _type = "mpc_local_planner_msgs/OptimalControlResult"
  _has_header = True  # flag to mark the presence of a Header object
  _full_text = """std_msgs/Header header

int64 dim_states
int64 dim_controls

float64[] time_states
float64[] states # Column Major
float64[] time_controls
float64[] controls # Column Major

bool optimal_solution_found
float64 cpu_time

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
"""
  __slots__ = ['header','dim_states','dim_controls','time_states','states','time_controls','controls','optimal_solution_found','cpu_time']
  _slot_types = ['std_msgs/Header','int64','int64','float64[]','float64[]','float64[]','float64[]','bool','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,dim_states,dim_controls,time_states,states,time_controls,controls,optimal_solution_found,cpu_time

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(OptimalControlResult, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.dim_states is None:
        self.dim_states = 0
      if self.dim_controls is None:
        self.dim_controls = 0
      if self.time_states is None:
        self.time_states = []
      if self.states is None:
        self.states = []
      if self.time_controls is None:
        self.time_controls = []
      if self.controls is None:
        self.controls = []
      if self.optimal_solution_found is None:
        self.optimal_solution_found = False
      if self.cpu_time is None:
        self.cpu_time = 0.
    else:
      self.header = std_msgs.msg.Header()
      self.dim_states = 0
      self.dim_controls = 0
      self.time_states = []
      self.states = []
      self.time_controls = []
      self.controls = []
      self.optimal_solution_found = False
      self.cpu_time = 0.

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
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2q().pack(_x.dim_states, _x.dim_controls))
      length = len(self.time_states)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.time_states))
      length = len(self.states)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.states))
      length = len(self.time_controls)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.time_controls))
      length = len(self.controls)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.Struct(pattern).pack(*self.controls))
      _x = self
      buff.write(_get_struct_Bd().pack(_x.optimal_solution_found, _x.cpu_time))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.dim_states, _x.dim_controls,) = _get_struct_2q().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.time_states = s.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.states = s.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.time_controls = s.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.controls = s.unpack(str[start:end])
      _x = self
      start = end
      end += 9
      (_x.optimal_solution_found, _x.cpu_time,) = _get_struct_Bd().unpack(str[start:end])
      self.optimal_solution_found = bool(self.optimal_solution_found)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2q().pack(_x.dim_states, _x.dim_controls))
      length = len(self.time_states)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.time_states.tostring())
      length = len(self.states)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.states.tostring())
      length = len(self.time_controls)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.time_controls.tostring())
      length = len(self.controls)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.controls.tostring())
      _x = self
      buff.write(_get_struct_Bd().pack(_x.optimal_solution_found, _x.cpu_time))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.dim_states, _x.dim_controls,) = _get_struct_2q().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.time_states = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.states = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.time_controls = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      s = struct.Struct(pattern)
      end += s.size
      self.controls = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      _x = self
      start = end
      end += 9
      (_x.optimal_solution_found, _x.cpu_time,) = _get_struct_Bd().unpack(str[start:end])
      self.optimal_solution_found = bool(self.optimal_solution_found)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2q = None
def _get_struct_2q():
    global _struct_2q
    if _struct_2q is None:
        _struct_2q = struct.Struct("<2q")
    return _struct_2q
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_Bd = None
def _get_struct_Bd():
    global _struct_Bd
    if _struct_Bd is None:
        _struct_Bd = struct.Struct("<Bd")
    return _struct_Bd
