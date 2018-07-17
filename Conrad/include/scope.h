#ifndef SCOPE_H_INCLUDED
#define SCOPE_H_INCLUDED

#define GLM_ENABLE_EXPERIMENTAL

/* Defines a byte offset from an index offset */
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + offset)
#endif

/* Defines for VertexAttribPointer IDs */
#define VERTEX_BUFFER   0
#define COLOR_BUFFER    1
#define TEX_BUFFER      2

/* Paths */
#define TEXPATH "textures"
#define ALPHAONE_PATH TEXPATH "/alpha_onepx.png" // One pixel 100% alpha texture

#endif // SCOPE_H_INCLUDED
