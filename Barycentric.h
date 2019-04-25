class Vector3;


/**
 * This lightweight class represents a barycentric coordinate system that depends on three vertices in 3-space
 * With help of this class you can calculate cartesian values into the corresponding barycentric values
 * and vice versa. The memory usage of this classes instances is very low.
 *
 * @author Barn
 * @version 20121003
 */
template <class Real = float>
class Barycentric
{

private: // members

	// the vertices of the triangle in cartesian space
	Vector3* _v1;
	Vector3* _v2;
	Vector3* _v3;

	/**
	 * leads to destruction of the pointer-values of
	 * _xPos, _yPos and _zPos at destructor call
	 */
	bool _destroy;

public: // constructors & destructor

	/**
	 * @brief constructor #1.
	 * @param v1 The first vector that describes a point on a triangle.
	 * @param v2 The second vector that describes a point on a triangle.
	 * @param v3 The third vector that describes a point on a triangle.
	 */
	Barycentric( Vector3* v1, Vector3* v2, Vector3* v3, bool destroy = false);

	/**
	 * @brief destructor
	 */
	~Barycentric();

public: // methods

	/**
	 * @brief retrieves the cartesian coords of the given barycentric coordinates.
	 * @param x the barycentric coordinate that corresponds to the first vertex.
	 * @param y the barycentric coordinate that corresponds to the second vertex.
	 * @param z the barycentric coordinate that corresponds to the third vertex.
	 * @return returns the vertex in cartesian coordinates.
	 */
	Vector3 getCartesian( const Real x, const Real y, const Real z) const;

	/**
     * @brief gets the barycentric coords of the given cartesian coordinates projected onto the triangle.
	 * @param v the vertex to wich to find the barycentric coordinates.
	 * @return the barycentric coordinates that correspond to the on-the-triangle-plane projected companion of the given vector.
	 */
	Vector3 getBarycentric( Vector3* v) const;

	/**
	 * @brief indicates, whether the pointers that are specified in the constructor
	 * or by the set*Pos() methods shall be deleted at destruction time or not.
	 */
	void destroyMembersAtDestruction( bool b = true);

public: // setters & getters

	void setVertex1( Vector3* v, bool destroyOldValue = false);
	void setVertex2( Vector3* v, bool destroyOldValue = false);
	void setVertex3( Vector3* v, bool destroyOldValue = false);

	const Vector3& getVertex1() const;
	const Vector3& getVertex2() const;
	const Vector3& getVertex3() const;

	bool isDestroyMembersAtDestruction() const;
};
