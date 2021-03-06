#include "PipelineTest.h"
#include <trantor/net/EventLoop.h>
#include <atomic>

void PipelineTest::asyncHandleHttpRequest(const HttpRequestPtr &req, const std::function<void(const HttpResponsePtr &)> &callback)
{
    static std::atomic<int> counter{0};
    int c = counter.fetch_add(1);
    double delay = ((double)(10 - (c % 10))) / 10.0;
    trantor::EventLoop::getEventLoopOfCurrentThread()->runAfter(delay, [c, callback]() {
        auto resp = HttpResponse::newHttpResponse();
        auto str = formattedString("<P>the %dth response</P>", c);
        resp->setBody(std::move(str));
        callback(resp);
    });
}
