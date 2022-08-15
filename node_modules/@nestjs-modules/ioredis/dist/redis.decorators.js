"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.InjectRedis = void 0;
const common_1 = require("@nestjs/common");
const redis_utils_1 = require("./redis.utils");
const InjectRedis = (connection) => {
    return (0, common_1.Inject)((0, redis_utils_1.getRedisConnectionToken)(connection));
};
exports.InjectRedis = InjectRedis;
