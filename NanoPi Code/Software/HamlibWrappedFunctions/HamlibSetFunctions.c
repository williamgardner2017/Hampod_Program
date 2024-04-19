char* set_frequency(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // freq_t value = (freq_t) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    freq_t value = *((freq_t*)((void**)input)[2]);
    
    int retcode = rig_set_freq(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Frequency now %.3f\n", value);
        return output; 
    } else {
        printf("rig_set_freq: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_mode(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // rmode_t mode_value = *(rmode_t*) input[2]; 
    // pbwidth_t width_value = *(pbwidth_t*) input[3]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    rmode_t mode_value = *((rmode_t*)((void**)input)[2]);
    pbwidth_t width_value = *((pbwidth_t*)((void**)input)[3]);


    int retcode = rig_set_mode(rig, vfo, mode_value, width_value); 	
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Mode now %s, Passband now %ld\n", rig_strrmode(mode_value), width_value);
        return output; 
    } else {
        printf("set_current_mode: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_vfo(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t value = *(vfo_t*) input[1]; 

    RIG* rig = ((void**)input)[0];
    vfo_t value = *((vfo_t*)((void**)input)[1]);

    int retcode = rig_set_vfo(rig, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "VFO set to %s\n", rig_strvfo(value));
        return output; 
    } else {
        printf("rig_set_vfo: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* push_to_talk_converter_for_set (ptt_t* input) {
    if (*input == RIG_PTT_ON) {
        return "on"; 
    } else if (input == RIG_PTT_OFF) {
        return "off"; 
    } else {
        return "-1"; 
    }
}

char* set_ptt(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // ptt_t value = *(ptt_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    ptt_t value = *((ptt_t*)((void**)input)[2]);

    int retcode = rig_set_ptt(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "PTT set to %s\n", push_to_talk_converter_for_set(&value));
        return output; 
    } else {
        printf("rig_set_ptt: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

// char* get_dcd(RIG* rig, vfo_t vfo) {
//     dcd_t value; 
//     int retcode = rig_get_dcd(rig, vfo, &value)
//     if (retcode == RIG_OK) {
//         char* output = malloc(40); 
//         if (value == RIG_PTT_ON) {
//             snprintf(output, 40, "On\n", value);
//         } else {
//             snprintf(output, 40, "Off\n", value);
//         }
//         return output; 
//     } else {
//         printf("rig_get_dcd: error = %s\n", rigerror(retcode));
//         return "-1"; 
//     }
// }

char* set_rit_offset(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // shortfreq_t value = *(shortfreq_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    shortfreq_t value = *((shortfreq_t*)((void**)input)[2]);

    int retcode = rig_set_rit(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "RIT set to %ld\n", value);
        return output; 
    } else {
        printf("rig_set_rit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_xit_offset(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // shortfreq_t value = *(shortfreq_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    shortfreq_t value = *((shortfreq_t*)((void**)input)[2]);

    int retcode = rig_set_xit(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "XIT set to %ld\n", value);
        return output; 
    } else {
        printf("rig_set_xit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_tuning_step(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // shortfreq_t value = *(shortfreq_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    shortfreq_t value = *((shortfreq_t*)((void**)input)[2]);

    int retcode = rig_set_ts(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Tuning step set to %ld\n", value);
        return output; 
    } else {
        printf("rig_set_ts: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_CTCSS_sub_audible_tone(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // tone_t value = *(tone_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    tone_t value = *((tone_t*)((void**)input)[2]);

    int retcode = rig_set_ctcss_tone(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "CTCSS Tone set to %i\n", value);
        return output; 
    } else {
        printf("rig_set_ctcss_tone: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_encoding_digitally_coded_squelch_code(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // tone_t value = *(tone_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    tone_t value = *((tone_t*)((void**)input)[2]);

    int retcode = rig_set_dcs_code(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "DCS code set to %i\n", value);
        return output; 
    } else {
        printf("rig_set_dcs_code: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_CTCSS_sub_audible_squelch_tone(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // tone_t value = *(tone_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    tone_t value = *((tone_t*)((void**)input)[2]);

    int retcode = rig_set_ctcss_sql(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "CTCSS SQL set to %i\n", value);
        return output; 
    } else {
        printf("rig_set_ctcss_sql: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_continuous_tone_controlled_squelch_code(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // tone_t value = *(tone_t*) input[2]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    tone_t value = *((tone_t*)((void**)input)[2]);

    int retcode = rig_set_dcs_sql(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "DCS code set to %i\n", value);
        return output; 
    } else {
        printf("rig_set_dcs_sql: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

// This is for both the LEVEL and FUNC features. Pretty genius if you ask me. :)
// Hamlib is very thoughtful for giving a common interest between rig_set_level and rig_set_func. 
// char* set_level_or_func_wrapper(RIG *rig, vfo_t vfo, char* setting_string, void* input) {
// 	char* output = malloc(100); 
// 	if (strstr("LEVEL", setting_string)) {
// 		value_t value = (value_t) input; 
// 		rig_set_level (rig, vfo, rig_parse_func(setting_string), value); 
// 		snprintf(output, 100, "%d", value); 
//         return output; 
// 	} else if (strstr("FUNC", setting)) {
// 		int value = (int) input; 
// 		rig_set_func (rig, vfo, rig_parse_func(setting_string), value); 	
// 		snprintf(output, 100, "%s now %d", setting_string, value); 
//         return output; 
// 	} else {
//         return "-1"; 
//     }
// }

char* set_level(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // setting_t setting_value = *(setting_t*) input[2]; 
    // value_t value = *(value_t*) input[3]; 
    printf("I get here into the level function\n"); 
    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    setting_t setting_value = *(setting_t*)((void**)input)[2];
    double value_double = *((double*)((void**)input)[3]); 

    float value_float = (float)value_double; 

    printf("I finish casting\n"); 
	char* output = malloc(100); 
    rig_set_level (rig, vfo, setting_value, value_float); 
    snprintf(output, 100, "%s set to %.2f", rig_strlevel(setting_value), value_float); 
    printf("I finish entirely\n"); 
    return output; 
}

char* set_func(void* input) {
    // RIG* rig = (RIG*) input[0]; 
    // vfo_t vfo = *(vfo_t*) input[1]; 
    // setting_t setting_value = *(setting_t*) input[2]; 
    // value_t value = *(value_t*) input[3]; 

    RIG* rig = ((void**)input)[0];
    vfo_t vfo = *((vfo_t*)((void**)input)[1]);
    setting_t setting_value = (setting_t)(uintptr_t)((void**)input)[2];
    int value = (int)(uintptr_t)((void**)input)[3];

    printf("%i", value); 
	char* output = malloc(100); 
    rig_set_func (rig, vfo, setting_value, value); 	
    snprintf(output, 100, "%s set to %d", rig_strfunc(setting_value), value); 
    return output; 
}