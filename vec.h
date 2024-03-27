//=====================================================================
// vec.h
// 
//=====================================================================

#if !defined(H_VEC)
#define H_VEC

typedef struct {
    float x, y, z;
} vec_t;


void createVector(vec_t *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

void addVector(vec_t *v1, vec_t *v2, vec_t *result) {
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

void subtractVector(vec_t *v1, vec_t *v2, vec_t *result) {
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
}

void scaleVector(vec_t *v, float scale, vec_t *result) {
    result->x = v->x * scale;
    result->y = v->y * scale;
    result->z = v->z * scale;
}

void normalizeVector(vec_t *v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

void lookAt(vec_t *eye, vec_t *look, vec_t *returnee) {
    vec_t direction;
	subtractVector(look, eye, &direction);
	// make object look at the lookAtPos
	float _y = atan2(direction.x, direction.z) * 180 / M_PI + 90;
	float _z = atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z)) * 180 / M_PI;

    returnee->y = _y;
    returnee->z = _z;
}

float distance(vec_t *v1, vec_t *v2) {
    return sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2) + pow(v1->z - v2->z, 2));
}

#endif