#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define n int32_t
#define un uint32_t

static const char *pn;

static un atoi(const char *str, const uint8_t base) {
    if ((base < 2) || (base > 36))
        return 0;
    un value = 0;
    while (*str != '\0') {
        value *= base;
        switch (*str) {
          case '0':           value +=  0; break;
          case '1':           value +=  1; break;
          case '2':           value +=  2; break;
          case '3':           value +=  3; break;
          case '4':           value +=  4; break;
          case '5':           value +=  5; break;
          case '6':           value +=  6; break;
          case '7':           value +=  7; break;
          case '8':           value +=  8; break;
          case '9':           value +=  9; break;
          case 'A': case 'a': value += 10; break;
          case 'B': case 'b': value += 11; break;
          case 'C': case 'c': value += 12; break;
          case 'D': case 'd': value += 13; break;
          case 'E': case 'e': value += 14; break;
          case 'F': case 'f': value += 15; break;
          case 'G': case 'g': value += 16; break;
          case 'H': case 'h': value += 17; break;
          case 'I': case 'i': value += 18; break;
          case 'J': case 'j': value += 19; break;
          case 'K': case 'k': value += 20; break;
          case 'L': case 'l': value += 21; break;
          case 'M': case 'm': value += 22; break;
          case 'N': case 'n': value += 23; break;
          case 'O': case 'o': value += 24; break;
          case 'P': case 'p': value += 25; break;
          case 'Q': case 'q': value += 26; break;
          case 'R': case 'r': value += 27; break;
          case 'S': case 's': value += 28; break;
          case 'T': case 't': value += 29; break;
          case 'U': case 'u': value += 30; break;
          case 'V': case 'v': value += 31; break;
          case 'W': case 'w': value += 32; break;
          case 'X': case 'x': value += 33; break;
          case 'Y': case 'y': value += 34; break;
          case 'Z': case 'z': value += 35; break;
          default: return 0;
        }
        str++;
    }
    return value;
}

static uint8_t n_digits(un value, const uint8_t base) {
    uint8_t n = 1;
    while (value >= base) {
        value /= base;
        n++;
    }
    return n;
}

static char *itoa(un value, const uint8_t base) {
    if ((base < 2) || (base > 36))
        return "";
    char *rc = malloc((sizeof (char)) * (n_digits(value, base) + 1));
    {
        char *rc_p = rc;
        do {
            *(rc_p++) =
                "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210"
                "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                [35 + value % base];
            value /= base;
        } while (value);
        *(rc_p--) = '\0';
        char *low = rc;
        while (low < rc_p) {
            const char tmp = *low;
            *(low++) = *rc_p;
            *(rc_p--) = tmp;
        }
    }
    return rc;
}

int main(const int argc, const char *const argv[]) {
    pn = argv[0];
    uint8_t out_base = 10;
    un value;
    if (argc > 1) {
        uint8_t in_base = 10;
        const char *r_number = NULL;
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "--help")) {
                printf("USAGE:\n"
                       "\t%s <number> [-i <in_base>] [-o <out_base>]\n"
                       "Both <in_base> and <out_base> default to 10.\n",
                       argv[0]);
                return 0;
            }

            if (!strcmp(argv[i], "-i")) {
                if (!(++i < argc)) goto incomplete_argument;
                in_base = atoi(argv[i], 10);
                continue;
            }

            if (!strcmp(argv[i], "-o")) {
                if (!(++i < argc)) goto incomplete_argument;
                out_base = atoi(argv[i], 10);
                continue;
            }

            if (r_number == NULL) {
                r_number = argv[i];
                continue;
            }

            fprintf(stderr, "%s: unknown argument: \"%s\"\n",
                    argv[0], argv[i]);
            return 1;

          incomplete_argument:
            fprintf(stderr, "%s: argument \"%s\" requires a value\n",
                    argv[0], argv[i - 1]);
            return 1;
        }

        if (r_number == NULL) {
          noargs:
            fprintf(stderr, "%s: run with \"--help\" for usage.\n", argv[0]);
            return 1;
        }
        value = atoi(r_number, in_base);
    } else
        goto noargs;
    {
        char *const s = itoa(value, out_base);
        printf("%s\n", s);
        free(s);
    }
    return 0;
}
