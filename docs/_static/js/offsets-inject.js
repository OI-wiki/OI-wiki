document$.subscribe(function () {
    OffsetsInjectionReview instanceof Object && OffsetsInjectionReview.setupReview instanceof Function && OffsetsInjectionReview.setupReview(document.body, {
        apiEndpoint: "{apiEndpoint}", // api endpoint injected here, see: scripts/post-build/offsets-inject/task-handler.ts
    })
})