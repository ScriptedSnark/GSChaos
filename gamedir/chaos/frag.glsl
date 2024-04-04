// https://www.shadertoy.com/view/ldBSRd
// Created by caiwan in 2014-11-01
#version 150

out vec4 colorOUT;
uniform vec2 iResolution;
uniform float iTime;

#define PI 3.14159

vec2 random2(vec2 c) { float j = 4906.0*sin(dot(c,vec2(169.7, 5.8))); vec2 r; r.x = fract(512.0*j); j *= .125; r.y = fract(512.0*j);return r-0.5;}

const float F2 =  0.3660254;
const float G2 = -0.2113249;

float simplex2d(vec2 p){vec2 s = floor(p + (p.x+p.y)*F2),x = p - s - (s.x+s.y)*G2; float e = step(0.0, x.x-x.y); vec2 i1 = vec2(e, 1.0-e),  x1 = x - i1 - G2, x2 = x - 1.0 - 2.0*G2; vec3 w, d; w.x = dot(x, x); w.y = dot(x1, x1); w.z = dot(x2, x2); w = max(0.5 - w, 0.0); d.x = dot(random2(s + 0.0), x); d.y = dot(random2(s +  i1), x1); d.z = dot(random2(s + 1.0), x2); w *= w; w *= w; d *= w; return dot(d, vec3(70.0));}

vec3 rgb2yiq(vec3 color){return color * mat3(0.299,0.587,0.114,0.596,-0.274,-0.321,0.211,-0.523,0.311);}
vec3 yiq2rgb(vec3 color){return color * mat3(1.,0.956,0.621,1,-0.272,-0.647,1.,-1.107,1.705);}

vec3 convertRGB443quant(vec3 color){ vec3 out0 = mod(color,1./16.); out0.b = mod(color.b, 1./8.); return out0;}
vec3 convertRGB443(vec3 color){return color-convertRGB443quant(color);}

vec2 sincos( float x ){return vec2(sin(x), cos(x));}
vec2 rotate2d(vec2 uv, float phi){vec2 t = sincos(phi); return vec2(uv.x*t.y-uv.y*t.x, uv.x*t.x+uv.y*t.y);}
vec3 rotate3d(vec3 p, vec3 v, float phi){ v = normalize(v); vec2 t = sincos(-phi); float s = t.x, c = t.y, x =-v.x, y =-v.y, z =-v.z; mat4 M = mat4(x*x*(1.-c)+c,x*y*(1.-c)-z*s,x*z*(1.-c)+y*s,0.,y*x*(1.-c)+z*s,y*y*(1.-c)+c,y*z*(1.-c)-x*s,0.,z*x*(1.-c)-y*s,z*y*(1.-c)+x*s,z*z*(1.-c)+c,0.,0.,0.,0.,1.);return (vec4(p,1.)*M).xyz;}

float varazslat(vec2 position, float time){
	float color = 0.0;
	float t = 2.*time;
	color += sin(position.x*cos(t/10.0)*20.0 )+cos(position.x*cos(t/15.)*10.0 );
	color += sin(position.y*sin(t/ 5.0)*15.0 )+cos(position.x*sin(t/25.)*20.0 );
	color += sin(position.x*sin(t/10.0)*  .2 )+sin(position.y*sin(t/35.)*10.);
	color *= sin(t/10.)*.5;
	
	return color;
}

void main()
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
    uv = (uv-.5)*2.;
   
    vec3 vlsd = vec3(0,1,0);
    vlsd = rotate3d(vlsd, vec3(1.,1.,0.), iTime);
    vlsd = rotate3d(vlsd, vec3(1.,1.,0.), iTime);
    vlsd = rotate3d(vlsd, vec3(1.,1.,0.), iTime);
    
    vec2 
        v0 = .75 * sincos(.3457 * iTime + .3423) - simplex2d(uv * .917),
        v1 = .75 * sincos(.7435 * iTime + .4565) - simplex2d(uv * .521), 
        v2 = .75 * sincos(.5345 * iTime + .3434) - simplex2d(uv * .759);
    
    vec3 color = vec3(dot(uv-v0, vlsd.xy),dot(uv-v1, vlsd.yz),dot(uv-v2, vlsd.zx));
    
    color *= .2 + 2.5*vec3(
    	(16.*simplex2d(uv+v0) + 8.*simplex2d((uv+v0)*2.) + 4.*simplex2d((uv+v0)*4.) + 2.*simplex2d((uv+v0)*8.) + simplex2d((v0+uv)*16.))/32.,
        (16.*simplex2d(uv+v1) + 8.*simplex2d((uv+v1)*2.) + 4.*simplex2d((uv+v1)*4.) + 2.*simplex2d((uv+v1)*8.) + simplex2d((v1+uv)*16.))/32.,
        (16.*simplex2d(uv+v2) + 8.*simplex2d((uv+v2)*2.) + 4.*simplex2d((uv+v2)*4.) + 2.*simplex2d((uv+v2)*8.) + simplex2d((v2+uv)*16.))/32.
    );
    
    color = yiq2rgb(color);
    
    color *= 1.- .25* vec3(
    	varazslat(uv *.25, iTime + .5),
        varazslat(uv * .7, iTime + .2),
        varazslat(uv * .4, iTime + .7)
    );
    
    
    //fragColor = vec4(convertRGB443(color),1.0);
    
    
    color = vec3(pow(color.r, 0.45), pow(color.g, 0.45), pow(color.b, 0.45));

	colorOUT = vec4(color, 0.35);
}