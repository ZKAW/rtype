import clsx from 'clsx';
import Heading from '@theme/Heading';
import styles from './styles.module.css';

type FeatureItem = {
  title: string;
  description: JSX.Element;
};

const FeatureList: FeatureItem[] = [
  {
    title: 'Entity Component System',
    description: (
      <>
        An entity-component-system (ECS) architecture that is designed to
        maximize the flexibility and maintainability of your game code.
      </>
    ),
  },
  {
    title: 'UDP Server Protocol',
    description: (
      <>
        A custom UDP server protocol that is designed to be fast and efficient
        for real-time multiplayer games.
      </>
    ),
  },
  {
    title: 'Game Engine Modular Design',
    description: (
      <>
        A modular game engine design that allows you to easily extend and
        customize the engine to fit your game's needs.
      </>
    ),
  },
];

function Feature({title, description}: FeatureItem) {
  return (
    <div className={clsx('col col--4')}>
      <div className="text--center padding-horiz--md">
        <Heading as="h3">{title}</Heading>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures(): JSX.Element {
  return (
    <section className={styles.features}>
      <div className="container">
        <div className="row">
          {FeatureList.map((props, idx) => (
            <Feature key={idx} {...props} />
          ))}
        </div>
      </div>
    </section>
  );
}
