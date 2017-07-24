#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

uniform vec4 u_sound;
uniform sampler2D u_video;
uniform sampler2D u_texture1;

float d = 2.; // kernel offset  笔触粗细
float lookup(vec2 p, float dx, float dy)
{
    vec2 uv = -(p.xy + vec2(dx * d, dy * d)) / u_resolution.xy;
    vec4 c = texture2D(u_video, uv.xy);
    float res = 1.;
    // return as luma
    return res*c.r + res*c.g + res*c.b;
}

void main()
{
    vec2 p = gl_FragCoord.xy;
    // simple sobel edge detection
    float gx = 0.0;
    gx += -1.0 * lookup(p, -1.0, -1.0);
    gx += -2.0 * lookup(p, -1.0,  0.0);
    gx += -1.0 * lookup(p, -1.0,  1.0);
    gx +=  1.0 * lookup(p,  1.0, -1.0);
    gx +=  2.0 * lookup(p,  1.0,  0.0);
    gx +=  1.0 * lookup(p,  1.0,  1.0);
    
    float gy = 0.0;
    gy += -1.0 * lookup(p, -1.0, -1.0);
    gy += -2.0 * lookup(p,  0.0, -1.0);
    gy += -1.0 * lookup(p,  1.0, -1.0);
    gy +=  1.0 * lookup(p, -1.0,  1.0);
    gy +=  2.0 * lookup(p,  0.0,  1.0);
    gy +=  1.0 * lookup(p,  1.0,  1.0);
    
    // hack: use g^2 to conceal noise in the video
    float g = gx*gx + gy*gy;
    float g2 = g * .5;
    
    gl_FragColor = vec4(1.-g,1.-g,1.-g, 1.0);
}

