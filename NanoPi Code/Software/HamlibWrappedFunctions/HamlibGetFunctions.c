char* get_current_transceive_mode(RIG* rig) {
    int value; 
    int retcode = rig_get_trn(rig, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%i\n", value);
        return output; 
    } else {
        printf("rig_get_trn: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
    
}

char* get_current_frequency(RIG* rig, vfo_t vfo) {
    freq_t value; 
    int retcode = rig_get_freq(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%.3f\n", value);
        return output; 
    } else {
        printf("rig_get_freq: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_mode(RIG* rig, vfo_t vfo) {
    rmode_t mode_value; 
    pbwidth_t width_value; 
    int retcode = rig_get_mode(rig, vfo, &mode_value, &width_value); 	
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%s, %.3f\n", rig_strrmode(mode_value), width_value);
        return output; 
    } else {
        printf("get_current_mode: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_vfo(RIG* rig) {
    vfo_t value; 
    int retcode = rig_get_vfo(rig, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%s\n", rig_strvfo(value));
        return output; 
    } else {
        printf("rig_get_vfo: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_ptt(RIG* rig, vfo_t vfo) {
    ptt_t value; 
    int retcode = rig_get_ptt(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%s\n", push_to_talk_converter(value));
        return output; 
    } else {
        printf("rig_get_ptt: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* push_to_talk_converter (ptt_t* input) {
    switch (input) {
        case RIG_PTT_ON: 
            return "PTT_ON"; 
        case RIG_PTT_OFF: 
            return "PTT_OFF"; 
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

// char* get_current_repeater_shift (RIG* rig, vfo_t vfo) {
//     rptr_shift_t value; 
//     int retcode = rig_get_rptr_shift(rig, vfo, &value); 
//     if (retcode == RIG_OK) {
//         char* output = malloc(40); 
//         snprintf(output, 40, "%s\n", repeater_shift_converter(value));
//         return output; 
//     } else {
//         printf("rig_get_rptr_shift: error = %s\n", rigerror(retcode));
//         return "-1"; 
//     }
// }

// char* repeater_shift_converter (rptr_shift_t* input) {
//     switch (input) {
//         case RIG_RPT_SHIFT_NONE: 
//             return "0"; 
//         case RIG_RPT_SHIFT_MINUS: 
//             return "-"; 
//         case RIG_RPT_SHIFT_PLUS: 
//             return "+"; 
//         default: 
//             return "-1";

//     }
// }

// char* get_current_repeater_offset (RIG* rig, vfo_t vfo) {
//     shortfreq_t value; 
//     int retcode = rig_get_rptr_offs(rig, vfo, &value); 
//     if (retcode == RIG_OK) {
//         char* output = malloc(40); 
//         snprintf(output, 40, "%f\n", repeater_shift_converter(value));
//         return output; 
//     } else {
//         printf("rig_get_rptr_offs: error = %s\n", rigerror(retcode));
//         return "-1"; 
//     }
// }


char* get_current_rit_offset(RIG* rig, vfo_t vfo) {
    shortfreq_t value; 
    int retcode = rig_get_rit(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%.3f\n", value);
        return output; 
    } else {
        printf("rig_get_rit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_xit_offset(RIG* rig, vfo_t vfo) {
    shortfreq_t value; 
    int retcode = rig_get_xit(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%.3f\n", value);
        return output; 
    } else {
        printf("rig_get_xit: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_tuning_step(RIG* rig, vfo_t vfo) {
    shortfreq_t value; 
    int retcode = rig_get_ts(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%.3f\n", value);
        return output; 
    } else {
        printf("rig_get_ts: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_CTCSS_sub_audible_tone(RIG* rig, vfo_t vfo) {
    tone_t value; 
    int retcode = rig_get_ctcss_tone(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%i\n", value);
        return output; 
    } else {
        printf("rig_get_ctcss_tone: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_encoding_digitally_coded_squelch_code(RIG* rig, vfo_t vfo) {
    tone_t value; 
    int retcode = rig_get_dcs_code(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%i\n", value);
        return output; 
    } else {
        printf("rig_get_dcs_code: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_CTCSS_sub_audible_squelch_tone(RIG* rig, vfo_t vfo) {
    tone_t value; 
    int retcode = rig_get_ctcss_sql(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%i\n", value);
        return output; 
    } else {
        printf("rig_get_ctcss_sql: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

char* get_current_continuous_tone_controlled_squelch_code(RIG* rig, vfo_t vfo) {
    tone_t value; 
    int retcode = rig_get_dcs_sql(rig, vfo, &value); 
    if (retcode == RIG_OK) {
        char* output = malloc(40); 
        snprintf(output, 40, "%i\n", value);
        return output; 
    } else {
        printf("rig_get_dcs_sql: error = %s\n", rigerror(retcode));
        return "-1"; 
    }
}

// This is for both the LEVEL and FUNC features. Pretty genius if you ask me. :)
// Hamlib is very thoughtful for giving a common interest between rig_get_level and rig_get_func. 
char* get_level_or_func_wrapper(RIG *rig, vfo_t vfo, char* setting) {
	w
	char* output = malloc(40); 
	if (strstr("LEVEL", setting)) {
		value_t* value; 
		rig_get_level (rig, vfo, rig_parse_func(setting), &value); 
		snprintf(output, "%d", value); 
        return output; 
	} else if (strstr("FUNC", setting)) {
		int status; 
		rig_get_func (rig, vfo, rig_parse_func(setting), &status); 	
		snprintf(output, "%d", status); 
        return output; 
	} else {
        return "-1"; 
    }
	
}

// This switch case is for everything else that is not the LEVEL or FUNC features. This is the easiest way to get around all of the features not being the same. 
char* get_radio_switcher(RIG* rig, vfo_t vfo, int num) {
    switch(num) {
        case 1:
            return get_current_transceive_mode(rig);
        case 2:
            return get_current_frequency(rig, vfo);
        case 3:
            return get_current_mode(rig, vfo);
        case 4:
            return get_current_vfo(rig);
        case 5:
            return get_ptt(rig, vfo);
        case 6:
            return get_current_rit_offset(rig, vfo);
        case 7:
            return get_current_xit_offset(rig, vfo);
        case 8:
            return get_current_tuning_step(rig, vfo);
        case 9:
            return get_current_CTCSS_sub_audible_tone(rig, vfo);
        case 10:
            return get_current_encoding_digitally_coded_squelch_code(rig, vfo);
        case 11:
            return get_current_CTCSS_sub_audible_squelch_tone(rig, vfo);
        case 12:
            return get_current_continuous_tone_controlled_squelch_code(rig, vfo);
        default:
            return "-1";
    }
}
