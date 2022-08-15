"use strict";
var RedisModule_1;
Object.defineProperty(exports, "__esModule", { value: true });
exports.RedisModule = void 0;
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const redis_core_module_1 = require("./redis.core-module");
let RedisModule = RedisModule_1 = class RedisModule {
    static forRoot(options, connection) {
        return {
            module: RedisModule_1,
            imports: [redis_core_module_1.RedisCoreModule.forRoot(options, connection)],
            exports: [redis_core_module_1.RedisCoreModule],
        };
    }
    static forRootAsync(options, connection) {
        return {
            module: RedisModule_1,
            imports: [redis_core_module_1.RedisCoreModule.forRootAsync(options, connection)],
            exports: [redis_core_module_1.RedisCoreModule],
        };
    }
};
RedisModule = RedisModule_1 = (0, tslib_1.__decorate)([
    (0, common_1.Module)({})
], RedisModule);
exports.RedisModule = RedisModule;
