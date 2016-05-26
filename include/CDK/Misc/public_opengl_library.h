class OpenglInterfazPublic {

  static OpenglInterfazPublic * instance_ptr_;
  OpenglInterfazPublic();
  ~OpenglInterfazPublic();
public:
  static OpenglInterfazPublic & instace();
  /**
  * @brief Use material at engine or program in opengl
  */
  void useMaterial(unsigned  int id);
  int getUniformLocation(int program, char * name);
};