#version  120

attribute vec3 aPos;

attribute  vec3 vertexColors;

varying vec4 vertexColor;

void  main()
{
	gl_Position = vec4(aPos, 1.0);
	vertexColor = vec4(vertexColors, 1.0);
}
