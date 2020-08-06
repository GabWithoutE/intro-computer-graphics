# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight (
    const in vec3 direction,
    const in vec4 lightcolor,
    const in vec3 normal,
    const in vec3 halfvec,
    const in vec4 mydiffuse,
    const in vec4 myspecular,
    const in float myshininess
) {
    float nDotL = dot(normal, direction); // diffusion intensity
    vec4 lambert = mydiffuse * lightcolor * max(nDotL, 0.0);

    float nDotH = dot(normal, halfvec); // specular intensity
    vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ;

    return lambert + phong;
}

void main (void) 
{       
    if (enablelighting) {
        vec4 finalcolor = vec4(0, 0, 0, 0);

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader
        // Notes:
        //  - light positions will already be transformed (by modelview) when inputed

        const vec3 eyepos = vec3(0, 0, 0);
        vec4 _vertexpos = modelview * myvertex;
        vec3 vertexpos = _vertexpos.xyz / _vertexpos.w;
        vec3 eyedir = normalize(eyepos - vertexpos);

        vec4 _normal = transpose(inverse(modelview)) * vec4(mynormal, 1);
        vec3 normal = normalize(_normal.xyz / _normal.w);

        for (int i = 0; i < numused; i++){
            vec4 lightpos = lightposn[i]; // position of the light currently being iterated over

            vec3 lightdirdhom; // dehomogenized light direction
            if (lightpos.w != 0) {
                vec3 lightposdhom = lightpos.xyz / lightpos.w; // dehomogenized
                lightdirdhom = normalize(lightposdhom - vertexpos);
            } else {
                lightdirdhom = normalize(lightpos.xyz);
            }

            vec3 halfvec = normalize(lightdirdhom + eyedir); // dehomogenized halfvec for use in ComputeLight

            vec4 color = ComputeLight(
                lightdirdhom,
                lightcolor[i],
                normal,
                halfvec,
                diffuse,
                specular,
                shininess
            );

            finalcolor += color;
        }

        finalcolor += ambient + emission;

        fragColor = finalcolor;
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}
