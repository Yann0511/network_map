"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const Redis = require("ioredis");
const testing_1 = require("@nestjs/testing");
const redis_module_1 = require("./redis.module");
const redis_utils_1 = require("./redis.utils");
const redis_decorators_1 = require("./redis.decorators");
describe('RedisModule', () => {
    it('Instance Redis', () => (0, tslib_1.__awaiter)(void 0, void 0, void 0, function* () {
        const module = yield testing_1.Test.createTestingModule({
            imports: [redis_module_1.RedisModule.forRoot({
                    config: {
                        host: '127.0.0.1',
                        port: 6379,
                        password: '123456',
                    }
                })],
        }).compile();
        const app = module.createNestApplication();
        yield app.init();
        const redisModule = module.get(redis_module_1.RedisModule);
        expect(redisModule).toBeInstanceOf(redis_module_1.RedisModule);
        yield app.close();
    }));
    it('Instance Redis client provider', () => (0, tslib_1.__awaiter)(void 0, void 0, void 0, function* () {
        const module = yield testing_1.Test.createTestingModule({
            imports: [redis_module_1.RedisModule.forRoot({
                    config: {
                        name: '1',
                        host: '127.0.0.1',
                        port: 6379,
                        password: '123456',
                    }
                })],
        }).compile();
        const app = module.createNestApplication();
        yield app.init();
        const redisClient = module.get((0, redis_utils_1.getRedisConnectionToken)('1'));
        const redisClientTest = module.get((0, redis_utils_1.getRedisConnectionToken)('test'));
        expect(redisClient).toBeInstanceOf(Redis);
        expect(redisClientTest).toBeInstanceOf(Redis);
        yield app.close();
    }));
    it('inject redis connection', () => (0, tslib_1.__awaiter)(void 0, void 0, void 0, function* () {
        let TestProvider = class TestProvider {
            constructor(redis) {
                this.redis = redis;
            }
            getClient() {
                return this.redis;
            }
        };
        TestProvider = (0, tslib_1.__decorate)([
            (0, common_1.Injectable)(),
            (0, tslib_1.__param)(0, (0, redis_decorators_1.InjectRedis)()),
            (0, tslib_1.__metadata)("design:paramtypes", [Object])
        ], TestProvider);
        const module = yield testing_1.Test.createTestingModule({
            imports: [redis_module_1.RedisModule.forRoot({
                    config: {
                        host: '127.0.0.1',
                        port: 6379,
                        password: '123456',
                    }
                })],
            providers: [TestProvider],
        }).compile();
        const app = module.createNestApplication();
        yield app.init();
        const provider = module.get(TestProvider);
        expect(provider.getClient()).toBeInstanceOf(Redis);
        yield app.close();
    }));
});
