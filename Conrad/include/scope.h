#ifndef SCOPE_H_INCLUDED
#define SCOPE_H_INCLUDED

#define GLM_ENABLE_EXPERIMENTAL

#define UP_VECTOR 0.0, 0.0, 1.0

/* Defines a byte offset from an index offset */
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + offset)
#endif

/* Defines for VertexAttribPointer IDs */
#define VERTEX_BUFFER           0
#define COLOR_BUFFER            1
#define TEX_BUFFER              2
#define VERTEX_NORMAL_BUFFER    3

/* Paths */
#define TEXPATH "textures"
#define BLANKONE_PATH TEXPATH "/blank_onepx.png" // One pixel 100% blank texture

/* Shader defines */
#define LIGHTS_ARRAY_SHADER "lights"
#define LIGHTS_ARRAY_STRLEN 6

/* Shadow mapping */
#define SHADOWMAP_SIZE 1024

/* Textures IDs */
#define DEPTHBUFFER_TEXTURE0 10 // First index of a depth buffer texture OpenGL binding

/* Structures */
struct RGB {
    float r = 0.0, g = 0.0, b = 0.0;
    RGB() : r(0.0), g(0.0), b(0.0) {}
    RGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
    RGB(const RGB &c) : r(c.r), g(c.g), b(c.b) {}
};

#endif // SCOPE_H_INCLUDED
