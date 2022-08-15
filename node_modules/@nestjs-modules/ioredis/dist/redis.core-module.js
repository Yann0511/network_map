"use strict";
var RedisCoreModule_1;
Object.defineProperty(exports, "__esModule", { value: true });
exports.RedisCoreModule = void 0;
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const redis_utils_1 = require("./redis.utils");
let RedisCoreModule = RedisCoreModule_1 = class RedisCoreModule {
    static forRoot(options, connection) {
        const redisOptionsProvider = {
            provide: (0, redis_utils_1.getRedisOptionsToken)(connection),
            useValue: options,
        };
        const redisConnectionProvider = {
            provide: (0, redis_utils_1.getRedisConnectionToken)(connection),
            useValue: (0, redis_utils_1.createRedisConnection)(options),
        };
        return {
            module: RedisCoreModule_1,
            providers: [
                redisOptionsProvider,
                redisConnectionProvider,
            ],
            exports: [
                redisOptionsProvider,
                redisConnectionProvider,
            ],
        };
    }
    static forRootAsync(options, connection) {
        const redisConnectionProvider = {
            provide: (0, redis_utils_1.getRedisConnectionToken)(connection),
            useFactory(options) {
                return (0, redis_utils_1.createRedisConnection)(options);
            },
            inject: [(0, redis_utils_1.getRedisOptionsToken)(connection)],
        };
        return {
            module: RedisCoreModule_1,
            imports: options.imports,
            providers: [...this.createAsyncProviders(options, connection), redisConnectionProvider],
            exports: [redisConnectionProvider],
        };
    }
    static createAsyncProviders(options, connection) {
        if (!(options.useExisting || options.useFactory || options.useClass)) {
            throw new Error('Invalid configuration. Must provide useFactory, useClass or useExisting');
        }
        if (options.useExisting || options.useFactory) {
            return [
                this.createAsyncOptionsProvider(options, connection)
            ];
        }
        return [
            this.createAsyncOptionsProvider(options, connection),
            { provide: options.useClass, useClass: options.useClass },
        ];
    }
    static createAsyncOptionsProvider(options, connection) {
        if (!(options.useExisting || options.useFactory || options.useClass)) {
            throw new Error('Invalid configuration. Must provide useFactory, useClass or useExisting');
        }
        if (options.useFactory) {
            return {
                provide: (0, redis_utils_1.getRedisOptionsToken)(connection),
                useFactory: options.useFactory,
                inject: options.inject || [],
            };
        }
        return {
            provide: (0, redis_utils_1.getRedisOptionsToken)(connection),
            useFactory(optionsFactory) {
                return (0, tslib_1.__awaiter)(this, void 0, void 0, function* () {
                    return yield optionsFactory.createRedisModuleOptions();
                });
            },
            inject: [options.useClass || options.useExisting],
        };
    }
};
RedisCoreModule = RedisCoreModule_1 = (0, tslib_1.__decorate)([
    (0, common_1.Global)(),
    (0, common_1.Module)({})
], RedisCoreModule);
exports.RedisCoreModule = RedisCoreModule;
