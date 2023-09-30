//
// Created by Arya Rakha on 9/27/2023.
//

#ifndef EASE_H
#define EASE_H

#include <cmath>
#include <stdexcept>

namespace Ease {

    inline double linear(double start, double end, double alpha) {
        return start + (end - start) * alpha;
    }

    inline double inSine(double start, double end, double alpha) {
        return start + (end - start) * (1 - cos(alpha * M_PI_2));
    }

    inline double outSine(double start, double end, double alpha) {
        return start + (end - start) * sin(alpha * M_PI_2);
    }

    inline double inOutSine(double start, double end, double alpha) {
        return start + (end - start) * 0.5 * (1 - cos(alpha * M_PI));
    }

    inline double inQuad(double start, double end, double alpha) {
        return start + (end - start) * alpha * alpha;
    }

    inline double outQuad(double start, double end, double alpha) {
        return start + (end - start) * (1 - (1 - alpha) * (1 - alpha));
    }

    inline double inOutQuad(double start, double end, double alpha) {
        alpha *= 2;
        if (alpha < 1) return start + (end - start) * 0.5 * alpha * alpha;
        alpha--;
        return start - (end - start) * 0.5 * (alpha * (alpha - 2) - 1);
    }

    inline double inCubic(double start, double end, double alpha) {
        return start + (end - start) * alpha * alpha * alpha;
    }

    inline double outCubic(double start, double end, double alpha) {
        return start + (end - start) * (1 - pow(1 - alpha, 3));
    }

    inline double inOutCubic(double start, double end, double alpha) {
        alpha *= 2;
        if (alpha < 1) return start + (end - start) / 2 * alpha * alpha * alpha;
        alpha -= 2;
        return start + (end - start) / 2 * (alpha * alpha * alpha + 2);
    }

    inline double inQuart(double start, double end, double alpha) {
        return start + (end - start) * alpha * alpha * alpha * alpha;
    }

    inline double outQuart(double start, double end, double alpha) {
        return start + (end - start) * (1 - pow(1 - alpha, 4));
    }

    inline double inOutQuart(double start, double end, double alpha) {
        alpha *= 2;
        if (alpha < 1) return start + (end - start) / 2 * alpha * alpha * alpha * alpha;
        alpha -= 2;
        return start - (end - start) / 2 * (alpha * alpha * alpha * alpha - 2);
    }

    inline double inQuint(double start, double end, double alpha) {
        return start + (end - start) * alpha * alpha * alpha * alpha * alpha;
    }

    inline double outQuint(double start, double end, double alpha) {
        return start + (end - start) * (1 - pow(1 - alpha, 5));
    }

    inline double inOutQuint(double start, double end, double alpha) {
        alpha *= 2;
        if (alpha < 1) return start + (end - start) / 2 * alpha * alpha * alpha * alpha * alpha;
        alpha -= 2;
        return start + (end - start) / 2 * (alpha * alpha * alpha * alpha * alpha + 2);
    }

    inline double inExpo(double start, double end, double alpha) {
        return (alpha == 0) ? start : start + (end - start) * pow(2, 10 * (alpha - 1));
    }

    inline double outExpo(double start, double end, double alpha) {
        return (alpha == 1) ? end : start + (end - start) * (1 - pow(2, -10 * alpha));
    }

    inline double inOutExpo(double start, double end, double alpha) {
        if (alpha == 0) return start;
        if (alpha == 1) return end;
        alpha *= 2;
        if (alpha < 1) return start + (end - start) / 2 * pow(2, 10 * (alpha - 1));
        alpha--;
        return start + (end - start) / 2 * (-pow(2, -10 * alpha) + 2);
    }

    inline double inCirc(double start, double end, double alpha) {
        return start - (end - start) * (sqrt(1 - alpha * alpha) - 1);
    }

    inline double outCirc(double start, double end, double alpha) {
        return start + (end - start) * sqrt(1 - pow(1 - alpha, 2));
    }

    inline double inOutCirc(double start, double end, double alpha) {
        alpha *= 2;
        if (alpha < 1) return start - (end - start) / 2 * (sqrt(1 - alpha * alpha) - 1);
        alpha -= 2;
        return start + (end - start) / 2 * (sqrt(1 - alpha * alpha) + 1);
    }

    inline double inBack(double start, double end, double alpha) {
        const double s = 1.70158f;
        return start + (end - start) * alpha * alpha * ((s + 1) * alpha - s);
    }

    inline double outBack(double start, double end, double alpha) {
        const double s = 1.70158;
        alpha = 1 - alpha;
        return start + (end - start) * ((s + 1) * pow(alpha, 2) + s * pow(alpha, 3) + 1);
    }

    inline double inOutBack(double start, double end, double alpha) {
        double s = 1.70158f;
        s *= 1.525f;
        alpha *= 2;
        if (alpha < 1) return start + (end - start) / 2 * (alpha * alpha * ((s + 1) * alpha - s));
        alpha -= 2;
        return start + (end - start) / 2 * (alpha * alpha * ((s + 1) * alpha + s) + 2);
    }

    inline double inElastic(double start, double end, double alpha) {
        if (alpha == 0) return start;
        if (alpha == 1) return end;
        double p = 0.3f;
        double a = end - start;
        double s = p / 4;
        alpha--;
        return -(a * pow(2, 10 * alpha) * sin((alpha - s) * (2 * M_PI) / p)) + start;
    }

    inline double outElastic(double start, double end, double alpha) {
        double p = 0.3;
        double s = p / 4;
        return start + (end - start) * pow(2, -10 * alpha) * sin((alpha - s) * (2 * M_PI) / p) + (end - start);
    }

    inline double inOutElastic(double start, double end, double alpha) {
        if (alpha == 0) return start;
        if (alpha == 1) return end;
        double p = 0.45f;
        double a = end - start;
        double s = p / 4;
        alpha *= 2;
        if (alpha < 1) {
            alpha--;
            return -0.5f * (a * pow(2, 10 * alpha) * sin((alpha - s) * (2 * M_PI) / p)) + start;
        }
        alpha--;
        return a * pow(2, -10 * alpha) * sin((alpha - s) * (2 * M_PI) / p) * 0.5f + end;
    }

    inline double outBounce(double start, double end, double alpha) {
        double n1 = 7.5625;
        double d1 = 2.75;
        double diff = end - start;

        if (alpha < 1 / d1) {
            return start + diff * (n1 * alpha * alpha);
        } else if (alpha < 2 / d1) {
            alpha -= 1.5 / d1;
            return start + diff * (n1 * alpha * alpha + 0.75);
        } else if (alpha < 2.5 / d1) {
            alpha -= 2.25 / d1;
            return start + diff * (n1 * alpha * alpha + 0.9375);
        } else {
            alpha -= 2.625 / d1;
            return start + diff * (n1 * alpha * alpha + 0.984375);
        }
    }

    inline double inBounce(double start, double end, double alpha) {
        return start + (end - start) * (1 - outBounce(0, 1, 1 - alpha));
    }

    inline double inOutBounce(double start, double end, double alpha) {
        if (alpha < 0.5f) {
            return start + (end - start) * 0.5f * (1 - outBounce(0, 1, 1 - 2 * alpha));
        } else {
            return start + (end - start) * 0.5f * (1 + outBounce(0, 1, 2 * alpha - 1));
        }
    }



    enum class Type {
        Linear,
        InSine, OutSine, InOutSine,
        InQuad, OutQuad, InOutQuad,
        InCubic, OutCubic, InOutCubic,
        InQuart, OutQuart, InOutQuart,
        InQuint, OutQuint, InOutQuint,
        InExpo, OutExpo, InOutExpo,
        InCirc, OutCirc, InOutCirc,
        InBack, OutBack, InOutBack,
        InElastic, OutElastic, InOutElastic,
        InBounce, OutBounce, InOutBounce
    };

    static double Calculate(Type easeType, double start, double end, double alpha) {
        switch (easeType) {
            case Type::Linear: return linear(start, end, alpha);
            case Type::InSine: return inSine(start, end, alpha);
            case Type::OutSine: return outSine(start, end, alpha);
            case Type::InOutSine: return inOutSine(start, end, alpha);
            case Type::InQuad: return inQuad(start, end, alpha);
            case Type::OutQuad: return outQuad(start, end, alpha);
            case Type::InOutQuad: return inOutQuad(start, end, alpha);
            case Type::InCubic: return inCubic(start, end, alpha);
            case Type::OutCubic: return outCubic(start, end, alpha);
            case Type::InOutCubic: return inOutCubic(start, end, alpha);
            case Type::InQuart: return inQuart(start, end, alpha);
            case Type::OutQuart: return outQuart(start, end, alpha);
            case Type::InOutQuart: return inOutQuart(start, end, alpha);
            case Type::InQuint: return inQuint(start, end, alpha);
            case Type::OutQuint: return outQuint(start, end, alpha);
            case Type::InOutQuint: return inOutQuint(start, end, alpha);
            case Type::InExpo: return inExpo(start, end, alpha);
            case Type::OutExpo: return outExpo(start, end, alpha);
            case Type::InOutExpo: return inOutExpo(start, end, alpha);
            case Type::InCirc: return inCirc(start, end, alpha);
            case Type::OutCirc: return outCirc(start, end, alpha);
            case Type::InOutCirc: return inOutCirc(start, end, alpha);
            case Type::InBack: return inBack(start, end, alpha);
            case Type::OutBack: return outBack(start, end, alpha);
            case Type::InOutBack: return inOutBack(start, end, alpha);
            case Type::InElastic: return inElastic(start, end, alpha);
            case Type::OutElastic: return outElastic(start, end, alpha);
            case Type::InOutElastic: return inOutElastic(start, end, alpha);
            case Type::InBounce: return inBounce(start, end, alpha);
            case Type::OutBounce: return outBounce(start, end, alpha);
            case Type::InOutBounce: return inOutBounce(start, end, alpha);
            default: throw std::invalid_argument("Invalid easing type");
        }
    }
}
#endif //EASE_H
