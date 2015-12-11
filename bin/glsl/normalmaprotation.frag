uniform sampler2D texture;
uniform float rotation;

void main(void)
{
	mat4 rotationMatrix = mat4(
		cos(rotation), -sin(rotation), 0., 0.,
		sin(rotation),  cos(rotation), 0., 0.,
		0., 0., 1., 0.,
		0., 0., 0., 1.
	);

	vec4 normal = texture2D(texture, gl_TexCoord[0].xy) * 2.0 - 1.0;
	normal = rotationMatrix * normal;
	gl_FragColor = (normal + 1.0) / 2.0;
}
