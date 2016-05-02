class OpenglInterfazPublic {
#define CDK_DRAW_MODE_TRIANGLES 0 
#define CDK_DRAW_MODE_STRIP_TRIANGLES 1
#define CDK_DRAW_MODE_POINTS 2

  OpenglInterfazPublic * instance_ptr_;
 //set ONE OF DEGINES
  
public:

  OpenglInterfazPublic & instace();
  OpenglInterfazPublic();
  ~OpenglInterfazPublic();

  //funcitons
  /**
  * @brief Use material at engine or program in opengl
  */
  void useMaterial(unsigned  int id);
  /**
  @brief Use this function to change the way which geometry is drawed
    by default is set to CDK_GL_TRIANGLES
  */
  void setDrawMode(int mode);
};