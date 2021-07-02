[[block]]
struct Uniform {
    view_proj: mat4x4<f32>;
};

[[group(0), binding(0)]]
var<uniform> uniform: Uniform;

[[group(1), binding(0)]]
var t_diffuse: texture_2d<f32>;

[[group(1), binding(1)]]
var s_diffuse: sampler;

struct VertexInput {
    [[location(0)]] position: vec3<f32>;
    [[location(1)]] normal: vec3<f32>;
    [[location(2)]] tangent: vec3<f32>;
    [[location(3)]] bitangent: vec3<f32>;
    [[location(4)]] color: vec4<f32>;
    [[location(5)]] tex_coords: vec2<f32>;
};

struct InstanceInput {
    [[location(6)]] model_0: vec4<f32>;
    [[location(7)]] model_1: vec4<f32>;
    [[location(8)]] model_2: vec4<f32>;
    [[location(9)]] model_3: vec4<f32>;
    [[location(10)]] normal_0: vec3<f32>;
    [[location(11)]] normal_1: vec3<f32>;
    [[location(12)]] normal_2: vec3<f32>;
};

struct VertexOutput {
    [[builtin(position)]] clip_position: vec4<f32>;
    [[location(0)]] position: vec3<f32>;
    [[location(1)]] normal: vec3<f32>;
    [[location(2)]] tangent: vec3<f32>;
    [[location(3)]] bitangent: vec3<f32>;
    [[location(4)]] color: vec4<f32>;
    [[location(5)]] tex_coords: vec2<f32>;
};

[[stage(vertex)]]
fn main(
    vertex: VertexInput,
    instance: InstanceInput,
) -> VertexOutput {
    var out: VertexOutput;
    let model = mat4x4<f32>(
        instance.model_0,
        instance.model_1,
        instance.model_2,
        instance.model_3,
    );
    let normal = mat3x3<f32>(
        instance.normal_0,
        instance.normal_1,
        instance.normal_2,
    );
    out.clip_position = uniform.view_proj * model * vec4<f32>(vertex.position, 1.0);
    out.position = vertex.position;
    out.normal = vertex.normal;
    out.tangent = vertex.tangent;
    out.bitangent = vertex.bitangent;
    out.color = vertex.color;
    out.tex_coords = vertex.tex_coords;
    return out;
}

[[stage(fragment)]]
fn main(in: VertexOutput) -> [[location(0)]] vec4<f32> {
    // return in.color;
    return textureSample(t_diffuse, s_diffuse, in.tex_coords);
}
