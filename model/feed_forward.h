//
// Created by dianh on 2021/04/16.
//

#ifndef SWIN_TRANSFORMER_CPP_FEED_FORWARD_H
#define SWIN_TRANSFORMER_CPP_FEED_FORWARD_H

#include "layer.h"
#include "tensor.h"
#include "linear.h"
#include "functions.h"

namespace shift_window_transformer {
    template<typename T>
    class FeedForward : virtual public Layer<T> {
    public:
        FeedForward(int dim, int hidden_dim) : dim(dim), hidden_dim(hidden_dim) {
            linear1 = new Linear<T>(dim, hidden_dim);
            linear2 = new Linear<T>(hidden_dim, dim);
        }

        ~FeedForward() {
            delete linear1;
            delete linear2;
        }

        void forward(const std::vector<T> &input, std::vector<T> &output) {
            std::vector<T> tmp1{};
            linear1->forward(input, tmp1);
            std::vector<T> tmp2{};
            for (auto item: tmp1) {
                tmp2.push_back(GELU(item));
            }
            linear2->forward(tmp2, output);
        }

    private:
        Linear <T> *linear1;
        Linear <T> *linear2;
        int dim;
        int hidden_dim;
    };
}
#endif //SWIN_TRANSFORMER_CPP_FEED_FORWARD_H