#pragma once

const int stop_token_max = 16;
const int ban_token_max = 16;
const int tensor_split_max = 16;
// match kobold's sampler list and order
enum samplers
{
    KCPP_SAMPLER_TOP_K=0,
    KCPP_SAMPLER_TOP_A=1,
    KCPP_SAMPLER_TOP_P=2,
    KCPP_SAMPLER_TFS=3,
    KCPP_SAMPLER_TYP=4,
    KCPP_SAMPLER_TEMP=5,
    KCPP_SAMPLER_REP_PEN=6,
    KCPP_SAMPLER_MAX
};
enum stop_reason
{
    INVALID=-1,
    OUT_OF_TOKENS=0,
    EOS_TOKEN=1,
    CUSTOM_STOPPER=2,
};
struct load_model_inputs
{
    const int threads;
    const int blasthreads;
    const int max_context_length;
    const bool low_vram;
    const bool use_mmq;
    const char * executable_path;
    const char * model_filename;
    const char * lora_filename;
    const char * lora_base;
    const bool use_mmap;
    const bool use_mlock;
    const bool use_smartcontext;
    const bool use_contextshift;
    const int clblast_info = 0;
    const int cublas_info = 0;
    const int blasbatchsize = 512;
    const int debugmode = 0;
    const int forceversion = 0;
    const int gpulayers = 0;
    const float rope_freq_scale = 1.0f;
    const float rope_freq_base = 10000.0f;
    const char * banned_tokens[ban_token_max];
    const float tensor_split[tensor_split_max];
};
struct generation_inputs
{
    const int seed;
    const char * prompt;
    const char * memory;
    const int max_context_length;
    const int max_length;
    const float temperature;
    const int top_k;
    const float top_a = 0.0f;
    const float top_p;
    const float min_p = 0.0f;
    const float typical_p;
    const float tfs;
    const float rep_pen;
    const int rep_pen_range;
    const float presence_penalty = 0.0f;
    const int mirostat = 0;
    const float mirostat_eta;
    const float mirostat_tau;
    const samplers sampler_order[KCPP_SAMPLER_MAX];
    const int sampler_len;
    const bool unban_tokens_rt;
    const char * stop_sequence[stop_token_max];
    const bool stream_sse;
    const char * grammar;
    const bool grammar_retain_state;
    const bool quiet = false;
};
struct generation_outputs
{
    int status = -1;
    char text[32768]; //32kb should be enough for any response
};
struct token_count_outputs
{
    int count = 0;
    int * ids; //we'll just use shared memory for this one, bit of a hack
};

extern std::string executable_path;
extern std::string lora_filename;
extern std::string lora_base;
extern std::vector<std::string> generated_tokens;
extern bool generation_finished;
extern float last_eval_time;
extern float last_process_time;
extern int last_token_count;
extern int total_gens;
extern stop_reason last_stop_reason;
