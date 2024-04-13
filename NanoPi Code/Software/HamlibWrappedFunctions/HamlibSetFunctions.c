// char* set_current_transceive_mode(RIG* rig, int value) {
//     int retcode = rig_set_trn(rig, value); 
//     if (retcode == RIG_OK) {
//         char* output = malloc(100); 
//         snprintf(output, 100, "\n", value);
//         return output; 
//     } else {
//         printf("rig_set_trn: error = %s\n", rigerror(retcode));
//         return "-1"; 
//     }
    
// }

char* set_frequency(RIG* rig, vfo_t vfo, freq_t value) {
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

char* set_mode(RIG* rig, vfo_t vfo, rmode_t mode_value, pbwidth_t width_value) {

    int retcode = rig_set_mode(rig, vfo, mode_value, width_value); 	
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Mode now %s, Passband now %.3f\n", rig_strrmode(mode_value), width_value);
        return output; 
    } else {
        printf("set_current_mode: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_vfo(RIG* rig, vfo_t value) {
    int retcode = rig_set_vfo(rig, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Current VFO now %s\n", rig_strvfo(value));
        return output; 
    } else {
        printf("rig_set_vfo: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_ptt(RIG* rig, vfo_t vfo, ptt_t value) {
    int retcode = rig_set_ptt(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Push to talk now %s\n", push_to_talk_converter(value));
        return output; 
    } else {
        printf("rig_set_ptt: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* push_to_talk_converter (ptt_t input) {
    switch (input) {
        case RIG_PTT_ON: 
            return "on"; 
        case RIG_PTT_OFF: 
            return "off"; 
        default: 
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

char* set_rit_offset(RIG* rig, vfo_t vfo, shortfreq_t value) { 
    int retcode = rig_set_rit(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "RIT now %.3f\n", value);
        return output; 
    } else {
        printf("rig_set_rit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_xit_offset(RIG* rig, vfo_t vfo, shortfreq_t value) {
    int retcode = rig_set_xit(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "XIT now %.3f\n", value);
        return output; 
    } else {
        printf("rig_set_xit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_tuning_step(RIG* rig, vfo_t vfo, shortfreq_t value) {
    int retcode = rig_set_ts(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "%.3f\n", value);
        return output; 
    } else {
        printf("rig_set_ts: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_CTCSS_sub_audible_tone(RIG* rig, vfo_t vfo, tone_t value) {
    int retcode = rig_set_ctcss_tone(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "CTCSS sub-tone frequency now %i\n", value);
        return output; 
    } else {
        printf("rig_set_ctcss_tone: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_encoding_digitally_coded_squelch_code(RIG* rig, vfo_t vfo, tone_t value) { 
    int retcode = rig_set_dcs_code(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "Encoding DCS code now %i\n", value);
        return output; 
    } else {
        printf("rig_set_dcs_code: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_CTCSS_sub_audible_squelch_tone(RIG* rig, vfo_t vfo, tone_t value) {
    int retcode = rig_set_ctcss_sql(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "CTCSS squelch now %i\n", value);
        return output; 
    } else {
        printf("rig_set_ctcss_sql: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* set_current_continuous_tone_controlled_squelch_code(RIG* rig, vfo_t vfo, tone_t value) {
    int retcode = rig_set_dcs_sql(rig, vfo, value); 
    if (retcode == RIG_OK) {
        char* output = malloc(100); 
        snprintf(output, 100, "DCS code now %i\n", value);
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

char* set_level(RIG *rig, vfo_t vfo, setting_t setting_value, value_t input) {
	char* output = malloc(100); 
    rig_set_level (rig, vfo, setting_value, value); 
    snprintf(output, 100, "%s now %d", rig_strlevel(setting_string), value); 
    return output; 
}

char* set_func(RIG *rig, vfo_t vfo, setting_t setting_value, value_t input) {
	char* output = malloc(100); 
    int value = (int) input; 
    rig_set_func (rig, vfo, rig_parse_func(setting_string), value); 	
    snprintf(output, 100, "%s now %d", rig_strfunc(setting_string), value); 
    return output; 
}