#ifndef __H_BUFFER__
#define __H_BUFFER__


#include <vector>
#include <memory>
#include <list>


/**
* buffer.h
* @author Alejandro Canela Mendez
* @brief This class represents a buffer.
*/
class Buffer{

public:

  Buffer(float*positions, float*normals, float*uvs,
    unsigned int* indexes);
  Buffer();
  /**
  * @brief This function is used to load the attributes for a mesh. This attributes are,
  * positions, normals , uvs and indices.
  * 
  * The order of the attributes it's important. You must order the data in group of three ,that
  * represents a vertex.

  * Example:
  * 
  *  1.0, 1.0 ,1.0 Vertex 1
  *  0.0, 0.0 ,0.0 Vertex 2
  *  1.0, 0.0 ,1.0 Vertex 2
  *  ..... 
  * ......
  * @param positions Position attributes, all vertex of the mesh must be ordered.
  * @param normals  Normal attributes, all normals must be ordered.
  * @param uvs Texture coordinate , all uvs must be in order.
  * @param indexes Indexes to the mesh, must be in order respect the other attributes.

  */


  void loadData(std::shared_ptr<float*>loatpositions, std::shared_ptr<float*>normals, std::shared_ptr<float*>uvs,
    std::shared_ptr<unsigned int*> indexes);

  /**
  @brief Set the size of the different atributtes of the mesh
  @`param p Total vertex position
  @param n Total  normals
  @param uv Total uvs
  @param t Total tangents
  @param bt Total bitangents
  @param i Total indices
  */
  void setAttributeSize(int p, int n, int uv, int t, int bt, int i);
  /**
  * @brif This function initilices the buffer whit size.
  * @param size Buffer size
  */
	void init(int size);
  /**
  * @brief Returns if the buffer has been modified.
  * @return Return true if the buffer has been modified, otherwise returns false;
  */
	bool isDirty();
  /**
  * @brief This function allow us to set if the buffer is dirty or not.
  * 
  */
  void setDirty(bool d);
  /**
  * @brief This function return where the vao is ;
  * @return Where the vao is binding.
  */
	unsigned int* getVAO();
  /**
  * @brief Set vao of the buffer
  */
  void setVAO(unsigned int vao);
  /**
  * @brief This function return  vbos ;
  * @return Where the vbos is binding.
  */
	unsigned int* getVBO();
  /**
  * @brief This function return three vectors, whose are the attributes. ;
  * @return Return three vectors.
  */
  std::vector<float*> getAttributesT();
  /**
  * @brief This function return the indices list ;
  * @return Indices list.
  */
  unsigned int* getIndexesT();
  /**
  * @brief This function is used to call opengl to use the geometry, and return the instance of
  opengl_interfaz.
  * @return A pointer to opengl_interfaz.
  */
	;
  /**
  * @brief Return the total number of mesh vertex
  * @return total vertex
  */
  int vertexSize();
  /**
  * @brief Return number of normals
  * @return .
  */
  int normalSize();
  /**
  * @brief Return number of uvs
  * @return total number of uvs
  */
  int uvSize();
  /**
  * @brief Return number of tangents
  * @return The total number of tangents
  */
  int tangentSize();
  /**
  * @brief Return total of mesh bitangents
  * @return number of bitangents
  */
  int bitangentSize();
  /**
  * @brief Return total of mesh indices
  * @return number of inideces
  */
  int indiceSize();

  void loadData(std::unique_ptr<char[]>buffer_data);
  char* getData();
private:
  struct Data;
  Data *data_;
  
};




#endif