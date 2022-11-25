#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform float u_radius;
uniform vec2 u_center;

void main() {
	vec2 st = (gl_FragCoord.xy - u_center) / u_radius;
	float r = sqrt(st.x*st.x + st.y*st.y);
	float alpha = 0.5 + 0.5 * sin(r * 20.0 - u_time * 10.0);
	if(r < 0.2) {
		alpha = 1.0;
	}
	float phi = atan(st.x, st.y);
	float red = abs(sin(phi - u_time));
	float blue = abs(cos(phi - u_time));
	gl_FragColor = vec4(red, 0.0, blue, alpha);
}
