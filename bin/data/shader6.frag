

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;


void main() {
    vec3 color;
    float l;
    float z = u_time;

    for(int i=0;i<3;i++) {
        vec2 uv;
        vec2 st = gl_FragCoord.xy/u_resolution.xy;
        uv = st;
        st -= .5;
        st.x * =u_resolution.x/u_resolution.y;
        z +=.07;
        l = length(st);
        uv += st/l*(sin(z)+1.)*abs(sin(l*9.-z*2.));
        color[i]=.01/length(abs(mod(uv,1.)-.5));
    }
    gl_FragColor = vec4(color/l,u_time);
}