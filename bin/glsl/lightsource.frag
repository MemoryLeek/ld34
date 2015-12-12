#define PI 3.14159265358979323846

uniform sampler2D texture;
uniform sampler2D normalmap;
uniform vec2 resolution;

uniform vec4 lightColor;
uniform float lightHeight;

void main(void)
{
	vec2 norm = gl_TexCoord[0].st * 2.0 - 1.0;
	float theta = atan(norm.y, norm.x);

	float r = length(norm) - 0.003;
	float coord = (theta + PI) / (2.0 * PI);
	vec2 shadowMapTextureCoords = vec2(coord, 0.0);

	vec3 normal = texture2D(normalmap, vec2(gl_TexCoord[0].x, abs(gl_TexCoord[0].y - 1.))).rgb;
	vec3 direction = vec3(vec2(.5, .5) - (gl_FragCoord.xy / resolution.xy), lightHeight);

	vec3 N = normalize(normal * 2.0 - 1.0);
	vec3 L = normalize(direction);

	gl_FragColor = lightColor * vec4(vec3(1.0), step(r, texture2D(texture, shadowMapTextureCoords).r) * smoothstep(1.0, 0.0, r)) * max(dot(N, L), 0.0);
}
